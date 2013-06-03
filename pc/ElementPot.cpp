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

#include <QLCDNumber>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDial>
#include <QDebug>
#include "ElementPot.h"

ElementPot::ElementPot(PinConfig *pinConfig, QString name, QObject *parent)
    : AElement(pinConfig, name, parent)
{
}

void ElementPot::displayConfig()
{
    this->minValue = new QLineEdit();
    this->maxValue = new QLineEdit();
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(minValue);
    hbox->addWidget(maxValue);

    this->setConfigLayout(hbox);
}

void ElementPot::displayElem()
{
    int min;
    int max;

    QVBoxLayout *vbox = new QVBoxLayout();
    QDial *pot = new QDial();
    QLCDNumber *lcd = new QLCDNumber();
    bool ok;

    min = this->minValue->text().toInt(&ok);
    if (!ok)
        min = 0;

    max = this->maxValue->text().toInt(&ok);
    if (!ok)
        max = 255;

    qDebug() << "min: " << min;
    qDebug() << "max: " << max;

    pot->setMinimum(min);
    pot->setMaximum(max);

    connect(pot, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
    connect(pot, SIGNAL(valueChanged(int)), this, SLOT(sendValueToArduino(int)));

    vbox->addWidget(lcd);
    vbox->addWidget(pot);
    this->setDisplayLayout(vbox);
}
