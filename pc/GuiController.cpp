/* ***** BEGIN LICENSE BLOCK *****
 *
 * This file is part of arduino-control-interface.
 *
 * arduino-control-interface is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * arduino-control-interface is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with arduino-control-interface.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ***** END LICENSE BLOCK ***** */

#include <QMessageBox>
#include "GuiController.h"
#include "ui_Gui.h"
#include "PinController.h"
#include "AElement.h"
#include "ElementSlider.h"
#include "ElementPot.h"
#include "ElementPushButton.h"

#include <QInputDialog>
#include <QDebug>
#include <QSettings>
#include <QVariant>
#include <QFile>
#include <QDataStream>


GuiController::GuiController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui),
    arduino(this)
{
    ui->setupUi(this);
    PinController::initSerialization();

    this->elemFactory = ElementFactorySingleton::getInstance();
    this->elemFactory->registerElem<ElementSlider>();
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

void GuiController::addToTab1Layout(QWidget *widget)
{
    this->ui->tab1Layout->addWidget(widget);
}

QHBoxLayout *GuiController::getTab1Layout() const
{
    return this->ui->tab1Layout;
}

void GuiController::on_pushButtonConnect_clicked()
{
    try
    {
        this->arduino.initPort(ui->lineEditPort->text());
        QMessageBox::information(this, "Connected", "Connected to the device.");
    }
    catch (ArduinoError& e)
    {
        QMessageBox::warning(this, "Arduino", e.what());
    }
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

Arduino *GuiController::getArduino()
{
    return &this->arduino;
}

void GuiController::displayArduinoMessage(QString data)
{
    this->ui->textBrowserArduino->insertPlainText(data);
    QTextCursor c =  this->ui->textBrowserArduino->textCursor();
    c.movePosition(QTextCursor::End);
    this->ui->textBrowserArduino->setTextCursor(c);
}

void GuiController::on_actionSlider_triggered()
{
    qDebug() << "actionSlider triggered";

    AElement *slider = new ElementSlider(this);
    PinController *pin = this->addPinControl();

    if (pin)
    {
        pin->addElement(slider);
    }
}

void GuiController::on_actionPotar_triggered()
{
    qDebug() << "on_actionPotar_triggered";

//    AElement *pot = new ElementPot(this);
//    PinController *pin = this->addPinControl();

//    if (pin)
//        pin->addElement(pot);
}

void GuiController::on_actionButton_triggered()
{

}

void GuiController::on_actionSave_triggered()
{
    qDebug() << "Save, " << this->pinControllerList.size() << " elems.";

    PinController *config = this->pinControllerList.first();

    {
        QSettings settings("./save.xml", QSettings::IniFormat);
        settings.setValue("Elements", qVariantFromValue(*config));
    }

    QSettings settings("./save.xml", QSettings::IniFormat);
    PinController result = settings.value("Elements", qVariantFromValue(PinController())).value<PinController>();
    result.print();
}

void GuiController::on_actionLoad_triggered()
{
    qDebug() << "Load";

    QSettings settings("./save.xml", QSettings::IniFormat);

    PinController tmp = settings.value("Elements", qVariantFromValue(PinController())).value<PinController>();
    PinController *pin = new PinController(tmp);
    pin->print();

    pin->setUi(this);
    this->pinControllerList.push_back(pin);
}
