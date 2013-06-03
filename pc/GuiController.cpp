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
#include <QDebug>
#include "GuiController.h"
#include "ui_Gui.h"
#include "PinController.h"


GuiController::GuiController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui),
    arduino(this)
{
    ui->setupUi(this);
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

    pinControllerList.push_back(pin);
    return pin;
}

void GuiController::addToTab1Layout(QWidget *widget)
{
    this->ui->tab1Layout->addWidget(widget);
}

void GuiController::addToTab2Layout(QWidget *widget)
{
    this->ui->tab2Layout->insertWidget(this->ui->tab2Layout->count() - 2, widget);
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

void GuiController::on_pushButtonAddPin_clicked()
{
    PinConfig *pinConfig = new PinConfig(this);

    pinConfigList.push_back(pinConfig);
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
