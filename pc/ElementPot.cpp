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

#include "ElementPot.h"

#include <QLCDNumber>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDial>
#include <QDebug>
#include <QLabel>

ElementPot::ElementPot(QObject *parent)
    : AElement("Pot", AElement::OUT, parent)
{
    this->minValue = NULL;
    this->maxValue = NULL;
    this->displayVBox = NULL;
    this->pot = NULL;
    this->lcd = NULL;
}

ElementPot::ElementPot(ElementPot const &other)
    : AElement("Pot", AElement::OUT, 0)
{
    (void) other;
    this->minValue = NULL;
    this->maxValue = NULL;
    this->displayVBox = NULL;
    this->pot = NULL;
    this->lcd = NULL;
}

ElementPot::~ElementPot()
{

}

void ElementPot::displayConfig()
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

void ElementPot::displayElem()
{
    int min = 0;
    int max = 255;

    this->displayVBox = new QVBoxLayout();
    this->pot = new QDial();
    this->lcd = new QLCDNumber();

    qDebug() << "min: " << min;
    qDebug() << "max: " << max;

    pot->setMinimum(min);
    pot->setMaximum(max);

    connect(pot, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
    connect(pot, SIGNAL(valueChanged(int)), this, SLOT(sendValueToDevice(int)));

    displayVBox->addWidget(lcd);
    displayVBox->addWidget(pot);
    this->setDisplayLayout(displayVBox);
}

void ElementPot::onApply()
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

    pot->setMinimum(min);
    pot->setMaximum(max);
}

void ElementPot::save()
{
    qDebug() << "Save pot";
    qDebug() << "min: " << this->pot->minimum();
    qDebug() << "max: " << this->pot->maximum();
    qDebug() << "value: " << this->pot->value();

    this->persistantData.push_back(this->pot->minimum());
    this->persistantData.push_back(this->pot->maximum());
    this->persistantData.push_back(this->pot->value());
}

void ElementPot::load()
{
    qDebug() << "Load pot";

    int min = this->persistantData.at(0).toInt();
    int max = this->persistantData.at(1).toInt();
    int value = this->persistantData.at(2).toInt();

    qDebug() << "min: " << min;
    qDebug() << "max: " << max;

    this->pot->setMinimum(min);
    this->pot->setMaximum(max);
    this->pot->setValue(value);
}
