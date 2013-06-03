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

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "ElementPushButton.h"

ElementPushButton::ElementPushButton(PinConfig *pinConfig, QObject *parent)
    : AElement(pinConfig, "Button", AElement::OUT, parent)
{
}

ElementPushButton::~ElementPushButton()
{

}

void ElementPushButton::displayConfig()
{
    this->lineEditValue = new QLineEdit();
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(this->lineEditValue);
    this->setConfigLayout(hbox);
}

void ElementPushButton::displayElem()
{
    QVBoxLayout *vbox = new QVBoxLayout();
    QPushButton *button = new QPushButton();
    bool ok;

    value = this->lineEditValue->text().toInt(&ok);
    if (!ok)
        value = 0;

    qDebug() << "val: " << value;

    button->setText("Send");

    connect(button, SIGNAL(clicked()), this, SLOT(sendValue()));

    vbox->addWidget(button);
    this->setDisplayLayout(vbox);
}

void ElementPushButton::sendValue()
{
    (void) value;
    this->sendValueToArduino(this->value);
}

