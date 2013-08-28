/* ***** BEGIN LICENSE BLOCK *****
 *
 * This file is part of waterbear-communication.
 *
 * waterbear-communication is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * waterbear-communication is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with waterbear-communication.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ***** END LICENSE BLOCK ***** */

#include <QMessageBox>
#include "GuiController.h"
#include "ui_Gui.h"
#include "ui_About.h"
#include "PinController.h"
#include "AElement.h"
#include "ElementSlider.h"
#include "ElementPot.h"
#include "ElementPushButton.h"
#include "ElementLCD.h"
#include "UDP.h"
#include "ConnectionController.h"

#include <QInputDialog>
#include <QDebug>
#include <QSettings>
#include <QVariant>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include "tcontainer.h"

GuiController::GuiController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui),
//    serial(this),
    communication(NULL),
    gridAuto(true),
    controllerConnect(NULL)
{
    ui->setupUi(this);
    PinController::initSerialization();

    this->controllerConnect = new ConnectionController(this);
    connect(this->controllerConnect, SIGNAL(connect(Communication::Type)),
            this, SLOT(initCommunication(Communication::Type)));

    this->elemFactory = ElementFactorySingleton::getInstance();
    this->elemFactory->registerElem<ElementSlider>();
    this->elemFactory->registerElem<ElementPot>();
    this->elemFactory->registerElem<ElementPushButton>();
    this->elemFactory->registerElem<ElementLCD>();

    this->editing = true;
//    Test
//    QLabel *lab1 = new QLabel("Label1");
//    QLabel *lab2 = new QLabel("Label2");
//    TContainer *con1 = new TContainer(this,QPoint(10,10),lab1);
//    TContainer *con2 = new TContainer(this,QPoint(20,50),lab2);
}

GuiController::~GuiController()
{
    while (!pinControllerList.isEmpty())
        delete pinControllerList.takeFirst();
    delete ui;
}

PinController *GuiController::addPinControl(quint8 pinNumber)
{
    PinController *pin = new PinController(this, pinNumber);

    this->pinControllerList.push_back(pin);
    return pin;
}

PinController *GuiController::addPinControl()
{
    static int pinNum = 0;
    PinController *pin;

    pin = new PinController(this, pinNum);
    pinControllerList.push_back(pin);
    ++pinNum;

    return pin;
}

QList<PinController *> *GuiController::getPinControllerList()
{
    return &this->pinControllerList;
}

// TODO: Put this in addPinControl.
void GuiController::addToTab1Layout(QWidget *widget)
{
    TContainer *pinContainer = new TContainer(this, QPoint(20,50), widget);
    pinContainerList.push_back(pinContainer);
//    this->ui->tab1Layout->addWidget(widget);
}

QWidget *GuiController::getTab1Layout() const
{
    return this->ui->tab1Layout;
}

bool GuiController::isGridAuto()
{
    return this->gridAuto;
}

bool GuiController::isEditing()
{
    return this->editing;
}

void GuiController::on_dockWidgetConsole_topLevelChanged(bool floating)
{
    qDebug() << "floating: " << floating;
    if (floating)
    {
        // TODO: does not work.
        //        QRect rect = this->ui->dockWidgetConsole->geometry();
        //        rect.setWidth(200);
        //        rect.setHeight(600);
        //        this->ui->dockWidgetConsole->setGeometry(rect);
    }
}

Communication *GuiController::getCommunication()
{
    return this->communication;
}

void GuiController::displayConsoleMessage(QString data)
{
    this->ui->textBrowserConsole->insertPlainText(data);
    QTextCursor c =  this->ui->textBrowserConsole->textCursor();
    c.movePosition(QTextCursor::End);
    this->ui->textBrowserConsole->setTextCursor(c);
}

void GuiController::on_actionSlider_triggered()
{
    qDebug() << "actionSlider triggered";

    AElement *slider = new ElementSlider(this);
    PinController *pin = this->addPinControl();

    if (pin)
        pin->addElement(slider);
}

void GuiController::on_actionPotar_triggered()
{
    qDebug() << "on_actionPotar_triggered";

    AElement *pot = new ElementPot(this);
    PinController *pin = this->addPinControl();

    if (pin)
        pin->addElement(pot);
}

void GuiController::on_actionButton_triggered()
{
    qDebug() << "on_actionButton_triggered";

    AElement *button = new ElementPushButton(this);
    PinController *pin = this->addPinControl();

    if (pin)
        pin->addElement(button);
}

void GuiController::on_actionLCD_triggered()
{
    qDebug() << "on_actionLCD_triggered";

    AElement *lcd = new ElementLCD(this);
    PinController *pin = this->addPinControl();

    if (pin)
        pin->addElement(lcd);
}

void GuiController::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Layout"), "",
        tr("Config File (*.ini);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    qDebug() << "Save, " << this->pinControllerList.size() << " elems.";

    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginWriteArray("PinControllers");
    for (int i = 0; i < this->pinControllerList.size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("Elements", qVariantFromValue(*this->pinControllerList.at(i)));
    }
    settings.endArray();
}

void GuiController::on_actionLoad_triggered()
{
    qDebug() << "Load";

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Layout"), "",
        tr("Config File (*.ini);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    // Remove old elements.
    PinController *item;
    while (!this->pinControllerList.isEmpty())
    {
        item = this->pinControllerList.first();
        this->pinControllerList.removeFirst();
        delete item;
    }

    // Load configuration from file.
    QSettings settings(fileName, QSettings::IniFormat);
    int size = settings.beginReadArray("PinControllers");
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);

        PinController tmp = settings.value("Elements", qVariantFromValue(PinController())).value<PinController>();
        PinController *pin = new PinController(tmp);
        pin->print();

        pin->setUi(this);
        this->pinControllerList.push_back(pin);
    }
    settings.endArray();
}

void GuiController::on_actionClose_triggered()
{
    this->close();
}

void GuiController::on_actionAbout_triggered()
{
    QDialog *about = new QDialog(0,0);

    Ui_DialogAbout aboutUi;
    aboutUi.setupUi(about);
//    aboutUi.labelTitle->setFont(QFont(":/ressources/handsean.ttf", 27));

    about->show();
}

void GuiController::on_actionEditing_triggered()
{
    this->editing = this->ui->actionEditing->isChecked();

    for (int i = 0; i < this->pinContainerList.size(); ++i)
    {
        this->pinContainerList.at(i)->setEditing(this->editing);
    }

//    this->repaint();
}

void GuiController::on_actionGrid_auto_triggered()
{
    this->gridAuto = this->ui->actionGrid_auto->isChecked();
}

void GuiController::on_actionConnect_triggered()
{
    this->controllerConnect->show();
}

void GuiController::initCommunication(Communication::Type type)
{
    if (type == Communication::SERIAL)
    {
        this->communication = new Serial(this->controllerConnect->getSerialPort(),
                                      this, this);
        try
        {
            this->communication->init();
            QMessageBox::information(this, "Connected", "Connected to the device.");
        }
        catch (SerialError &e)
        {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
    else if (type == Communication::UDP)
    {
        this->communication = new UDP(this->controllerConnect->getIp(),
                                         this->controllerConnect->getIpPort(),
                                         this, this);
        this->communication->init();
        QMessageBox::information(this, "Connected", "Connected to the device.");
    }
}

void GuiController::transmitCmd(Communication::Buffer buffer)
{
    this->communication->transmitCmd(buffer);
}
