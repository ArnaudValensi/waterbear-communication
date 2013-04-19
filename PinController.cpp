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

#include <QVBoxLayout>
#include "PinController.h"

PinController::PinController(GuiController *ui, quint8 pinNumber, QObject *parent) :
    QObject(parent),
    pinNumber(pinNumber),
    ui(ui)
{
    this->groupBox = new QGroupBox();
    this->vertSlider = new QSlider(Qt::Vertical);
    this->maxValue = new QLineEdit();
    this->minValue = new QLineEdit();
    this->lcd = new QLCDNumber();

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(maxValue);
    vbox->addWidget(vertSlider);
    vbox->addWidget(minValue);
    vbox->addWidget(lcd);
    //vbox->addStretch(1);
    groupBox->setLayout(vbox);
    this->ui->addToTab1Layout(groupBox);

    groupBox->setTitle(QString("Pin %1").arg(pinNumber));
    maxValue->setText(QString::number(defaultMax));
    minValue->setText(QString::number(defaultMin));
    vertSlider->setRange(defaultMin, defaultMax);
//    maxValue->setMaxLength(3);
//    minValue->setMaxLength(3);
//    QRect maxValueRect = maxValue->geometry();
//    maxValueRect.setWidth(41);
//    maxValue->setGeometry(maxValueRect);

    //connect(vertSlider, &QSlider::valueChanged, lcd, &QLCDNumber::display);
    connect(vertSlider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
    connect(vertSlider, SIGNAL(valueChanged(int)), this, SLOT(sendValueToArduino(int)));
    connect(this, SIGNAL(sliderValueChanged(Arduino::Buffer)),
            ui->getArduino(), SLOT(transmitCmd(Arduino::Buffer)));
    connect(maxValue, SIGNAL(editingFinished()), this, SLOT(updateSliderRange()));
    connect(minValue, SIGNAL(editingFinished()), this, SLOT(updateSliderRange()));
}

void PinController::updateSliderRange()
{
    quint8 max = this->maxValue->text().toUShort();
    quint8 min = this->minValue->text().toUShort();

    vertSlider->setRange(min, max);
}

void PinController::sendValueToArduino(int value)
{
    Arduino::Buffer buffer(this->pinNumber, value);
    emit sliderValueChanged(buffer);
}
