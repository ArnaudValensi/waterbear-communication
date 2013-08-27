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

#include <QVBoxLayout>
#include <QSlider>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include "ElementSlider.h"


ElementSlider::ElementSlider(QObject *parent)
    : AElement("ElementSlider", AElement::OUT, parent)
{
    qDebug() << "ElementSlider Constructor";
    this->minValue = NULL;
    this->maxValue = NULL;
    this->displayVBox = NULL;
    this->slider = NULL;
}

ElementSlider::ElementSlider(ElementSlider const &other)
    : AElement("ElementSlider", AElement::OUT, 0)
{
    qDebug() << "ElementSlider Constructor Copy";
    (void) other;
    this->minValue = NULL;
    this->maxValue = NULL;
    this->displayVBox = NULL;
    this->slider = NULL;
//    this->minValue = other.minValue;
//    this->maxValue = other.maxValue;
//    this->displayVBox = other.displayVBox;
//    this->slider = other.slider;
//    this->lcd = other.lcd;
}

ElementSlider::~ElementSlider()
{

}

void ElementSlider::displayConfig()
{
    this->minValue = new QLineEdit();
    this->maxValue = new QLineEdit();
    QVBoxLayout *hbox = new QVBoxLayout();

    hbox->addWidget(new QLabel("Min:"));
    hbox->addWidget(minValue);
    hbox->addWidget(new QLabel("Max:"));
    hbox->addWidget(maxValue);

    this->setConfigLayout(hbox);
}

void ElementSlider::displayElem()
{
    int min = 0;
    int max = 255;

    this->displayVBox = new QVBoxLayout();
    this->slider = new QSlider();

    qDebug() << "min: " << min;
    qDebug() << "max: " << max;

//    QPalette Pal = this->lcd->palette();
//    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);
//    this->lcd->setPalette(Pal);
//    this->lcd->setStyleSheet("QLCDNumber { color : black; }");

    slider->setMinimum(min);
    slider->setMaximum(max);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sendValueToDevice(int)));

    displayVBox->addWidget(slider);
    this->setDisplayLayout(displayVBox);
}

void ElementSlider::onApply()
{
    bool ok;
    int min;
    int max;

    min = this->minValue->text().toInt(&ok);
    if (!ok)
        min = 0;

    max = this->maxValue->text().toInt(&ok);
    if (!ok)
        max = 255;

    slider->setMinimum(min);
    slider->setMaximum(max);
}

void ElementSlider::save()
{
    qDebug() << "Save Slider";
    qDebug() << "min: " << this->slider->minimum();
    qDebug() << "max: " << this->slider->maximum();

    this->persistantData.push_back(this->slider->minimum());
    this->persistantData.push_back(this->slider->maximum());
    this->persistantData.push_back(this->slider->value());
}

void ElementSlider::load()
{
    qDebug() << "Load Slider";

    int min = this->persistantData.at(0).toInt();
    int max = this->persistantData.at(1).toInt();
    int value = this->persistantData.at(2).toInt();

    qDebug() << "min: " << min;
    qDebug() << "max: " << max;

    this->slider->setMinimum(min);
    this->slider->setMaximum(max);
    this->slider->setValue(value);
}
