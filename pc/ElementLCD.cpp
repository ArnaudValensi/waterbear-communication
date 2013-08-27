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

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QLCDNumber>
#include "ElementLCD.h"

ElementLCD::ElementLCD(QObject *parent)
    : AElement("LCD", AElement::OUT, parent)
{

}

ElementLCD::ElementLCD(ElementLCD const &other)
    : AElement("LCD", AElement::OUT, 0)
{
    (void) other;
}

ElementLCD::~ElementLCD()
{

}

void ElementLCD::displayConfig()
{
    QHBoxLayout *hbox = new QHBoxLayout();
    this->setConfigLayout(hbox);
}

void ElementLCD::displayElem()
{
    QVBoxLayout *vbox = new QVBoxLayout();
    this->lcd = new QLCDNumber();

    vbox->addWidget(this->lcd);
    this->setDisplayLayout(vbox);
}

void ElementLCD::sendValue()
{

}

void ElementLCD::onApply()
{

}

void ElementLCD::save()
{
    qDebug() << "Save ElementLCD";
    qDebug() << "value: " << this->lcd->value();

    this->persistantData.push_back(this->lcd->value());
}

void ElementLCD::load()
{
    qDebug() << "Load ElementLCD";

    int value = this->persistantData.at(0).toInt();
}
