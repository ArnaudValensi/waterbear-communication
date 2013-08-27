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
    //this->lineEditValue = NULL;
    //this->value = 0;
}

ElementLCD::ElementLCD(ElementLCD const &other)
    : AElement("LCD", AElement::OUT, 0)
{
    (void) other;
//    this->lineEditValue = NULL;
//    this->value = 0;
}

ElementLCD::~ElementLCD()
{

}

void ElementLCD::displayConfig()
{
//    this->lineEditValue = new QLineEdit();
    QHBoxLayout *hbox = new QHBoxLayout();

//    hbox->addWidget(this->lineEditValue);
    this->setConfigLayout(hbox);
}

void ElementLCD::displayElem()
{
    QVBoxLayout *vbox = new QVBoxLayout();
    this->lcd = new QLCDNumber();

//    QPushButton *button = new QPushButton();

//    qDebug() << "val: " << value;

//    button->setText("Send");

//    connect(button, SIGNAL(clicked()), this, SLOT(sendValue()));

    vbox->addWidget(this->lcd);
    this->setDisplayLayout(vbox);
}

void ElementLCD::sendValue()
{
//    (void) value;
//    this->sendValueToDevice(this->value);
}

void ElementLCD::onApply()
{
//    bool ok;

//    this->value = this->lineEditValue->text().toInt(&ok);
//    if (!ok)
//        this->value = 0;
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

//    qDebug() << "value: " << this->value;

//    TODO: reload value
//    this->lcd->set
//    this->value = value;
}
