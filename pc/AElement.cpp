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

#include <QDebug>
#include <QDialog>
#include "AElement.h"
#include "PinConfig.h"

// Deprecated
AElement::AElement(PinConfig *pinConfig, QString name, TransfertType io, QObject *parent) :
    QObject(parent)
{
    qDebug() << "AElement Constructor";

    this->pinConfig = pinConfig;
    this->name = name;
    this->transfertType = io;
    this->configWindow = NULL;

    this->radioButton = new QRadioButton(name);
    QObject::connect(radioButton, SIGNAL(clicked(bool)), this, SLOT(displayOut()));
}

AElement::AElement(QString name, TransfertType io, QObject *parent) :
    QObject(parent)
{
    qDebug() << "AElement Copy Constructor";

//    this->pinConfig = pinConfig;
    this->name = name;
    this->transfertType = io;

    this->radioButton = new QRadioButton(name);
    QObject::connect(radioButton, SIGNAL(clicked(bool)), this, SLOT(displayOut()));
}

AElement::~AElement()
{

}

QString AElement::getName() const
{
    return this->name;
}

QRadioButton *AElement::getRadioButton() const
{
    return this->radioButton;
}

// TODO: Maybe can be replaced by the direct call of displayElem()
void AElement::displayOut()
{
//    this->pinConfig->preDisplayConfig();
    this->displayElem();
//    this->pinConfig->postDisplayConfig();
}

void AElement::openConfigWindow()
{
    if (!this->configWindow)
    {
        this->configWindow = new QDialog();
        this->configWindow->setLayout(this->configLayout);
    }
    this->configWindow->show();
    this->configWindow->activateWindow();
}

void AElement::closeConfigWindow()
{
    this->configWindow->close();
}

void AElement::setConfigLayout(QLayout *layout)
{
    // Add a 'OK' button and connect it to onApply() function
    QPushButton *apply = new QPushButton("OK");
    layout->addWidget(apply);
    connect(apply, SIGNAL(clicked()), this, SLOT(onApplyProc()));

    this->configLayout = layout;
}

void AElement::setDisplayLayout(QLayout *layout)
{
//    this->pinConfig->setLayout(layout);
    this->displayLayout = layout;
}

QLayout *AElement::getDisplayLayout() const
{
    return this->displayLayout;
}

QLayout *AElement::getConfigLayout() const
{
    return this->configLayout;
}

void AElement::sendValueToArduino(int value)
{
//    this->pinConfig->sendValueToArduino(value);
    qDebug() << "Sent to Arduino: " << value;
}

AElement::TransfertType AElement::getTransfertType()
{
    return this->transfertType;
}

void AElement::onApplyProc()
{
    this->onApply();
    this->closeConfigWindow();
}

// You have to reimplement this function in the child
void AElement::displayConfig()
{

}

// You have to reimplement this function in the child
void AElement::displayElem()
{

}

void AElement::onApply()
{

}

void AElement::initSerialization()
{
    qRegisterMetaTypeStreamOperators<AElement*>("AElement");

    qMetaTypeId<AElement*>();               // Teste la validité de la classe Contact
}

QDataStream &operator<<(QDataStream &out, const AElement *&value)
{
    qDebug() << "[AElement] QDataStream out: pin: " << value->name;

    out << value->name;

    return out;
}

QDataStream &operator>>(QDataStream &in, AElement *&value)
{
    value = new AElement();
    in >> value->name;

    qDebug() << "[AElement] QDataStream in: pin: " << value->name;

    return in;
}
