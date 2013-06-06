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

#include "ElementPot.h"

#include <QLCDNumber>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDial>
#include <QDebug>
#include <QLabel>

ElementPot::ElementPot(PinConfig *pinConfig, QObject *parent)
    : AElement(pinConfig, "Pot", AElement::OUT, parent)
{
    this->minValue = NULL;
    this->maxValue = NULL;
    this->displayVBox = NULL;
    this->pot = NULL;
    this->lcd = NULL;
}

ElementPot::ElementPot(QObject *parent)
    : AElement("Pot", AElement::OUT, parent)
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
    connect(pot, SIGNAL(valueChanged(int)), this, SLOT(sendValueToArduino(int)));

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
