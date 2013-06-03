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
    this->vbox = new QVBoxLayout();

    this->vbox->addWidget(this->maxValue);
    this->vbox->addWidget(this->vertSlider);
    this->vbox->addWidget(this->minValue);
    this->vbox->addWidget(this->lcd);
    //vbox->addStretch(1);
//    this->groupBox->setLayout(this->vbox);
    this->ui->addToTab1Layout(this->groupBox);

    this->groupBox->setTitle(QString("Pin %1").arg(this->pinNumber));
//    this->maxValue->setText(QString::number(this->defaultMax));
//    this->minValue->setText(QString::number(this->defaultMin));
//    this->vertSlider->setRange(this->defaultMin, this->defaultMax);
//    this->lcd->setSegmentStyle(QLCDNumber::Flat);
////    maxValue->setMaxLength(3);
////    minValue->setMaxLength(3);
////    QRect maxValueRect = maxValue->geometry();
////    maxValueRect.setWidth(41);
////    maxValue->setGeometry(maxValueRect);

//    //connect(vertSlider, &QSlider::valueChanged, lcd, &QLCDNumber::display);
//    connect(this->vertSlider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
//    connect(this->vertSlider, SIGNAL(valueChanged(int)), this, SLOT(sendValueToArduino(int)));
//    connect(this, SIGNAL(sliderValueChanged(Arduino::Buffer)),
//            ui->getArduino(), SLOT(transmitCmd(Arduino::Buffer)));
//    connect(this->maxValue, SIGNAL(editingFinished()), this, SLOT(updateSliderRange()));
//    connect(this->minValue, SIGNAL(editingFinished()), this, SLOT(updateSliderRange()));
}

void PinController::updateSliderRange()
{
//    quint8 max = this->maxValue->text().toUShort();
//    quint8 min = this->minValue->text().toUShort();

//    vertSlider->setRange(min, max);
}

void PinController::sendValueToArduino(int value)
{
    Arduino::Buffer buffer(this->pinNumber, value);
    emit sliderValueChanged(buffer);
}

void PinController::setLayout(QLayout *layout)
{
    this->groupBox->setLayout(layout);
}
