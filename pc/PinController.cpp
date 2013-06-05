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

#include "PinController.h"

#include <QMouseEvent>
#include <QDebug>

PinController::PinController(GuiController *ui, quint8 pinNumber, QWidget *parent) :
    QGroupBox(parent),
    pinNumber(pinNumber),
    ui(ui)
{
    this->setFixedWidth(this->fixedWidth);
    this->ui->addToTab1Layout(this);
    this->setTitle(QString("Pin %1").arg(this->pinNumber));

    Arduino *arduino = ui->getArduino();
    QObject::connect(this, SIGNAL(valueChanged(Arduino::Buffer)), arduino, SLOT(transmitCmd(Arduino::Buffer)));
}

void PinController::sendValueToArduino(int value)
{
    Arduino::Buffer buffer(this->pinNumber, value);
    emit valueChanged(buffer);
}

int PinController::getPinNumber() const
{
    return this->pinNumber;
}

void PinController::mousePressEvent(QMouseEvent *event)
{
    offset = event->pos();
}

void PinController::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(this->mapToParent(event->pos() - offset));
    }
}

void PinController::mouseReleaseEvent(QMouseEvent *event)
{
    // TODO: protect against the right click

    QHBoxLayout *layout = this->ui->getTab1Layout();
    QList<PinController *> pinControllerList = this->ui->getPinControllerList();

    int index = pinControllerList.indexOf(this);
    int mouseX = this->mapToParent(event->pos()).x();
    int newIndex = mouseX / PinController::fixedWidth;
    int listSize = pinControllerList.size();

    if (newIndex > listSize)
        newIndex = listSize;

    PinController *pinController = pinControllerList.at(index);
    pinControllerList.removeAt(index);
    pinControllerList.insert(newIndex, pinController);

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != NULL)
        layout->removeItem(item);

    foreach (PinController *p, pinControllerList) {
        layout->addWidget(p);
    }

    this->updateGeometry();
}
