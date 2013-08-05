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

#include <QDebug>
#include <QDialog>
#include "AElement.h"
#include "PinController.h"
//#include "ElementSlider.h"

// Deprecated
//AElement::AElement(PinConfig *pinConfig, QString name, TransfertType io, QObject *parent) :
//    QObject(parent)
//{
//    qDebug() << "AElement Constructor";

//    this->pinConfig = pinConfig;
//    this->name = name;
//    this->transfertType = io;
//    this->configWindow = NULL;

//    this->radioButton = new QRadioButton(name);
//    QObject::connect(radioButton, SIGNAL(clicked(bool)), this, SLOT(displayOut()));
//}

AElement::AElement(QString name, TransfertType io, QObject *parent)
    : QObject(parent)
{
    qDebug() << "AElement Constructor";

    this->configWindow = NULL;
    this->name = name;
    this->transfertType = io;
    this->configWindow = NULL;
    this->pin = NULL;

    this->radioButton = new QRadioButton(name);
    QObject::connect(radioButton, SIGNAL(clicked(bool)), this, SLOT(displayProc()));
}

AElement::AElement(AElement const &other)
    : QObject(0)
{
    qDebug() << "AElement Copy Constructor";

    this->name = other.name;
    this->transfertType = other.transfertType;
    this->configWindow = other.configWindow;
    this->pin = other.pin;

    this->radioButton = new QRadioButton(name);
    QObject::connect(radioButton, SIGNAL(clicked(bool)), this, SLOT(displayProc()));
}

AElement::~AElement()
{

}

void AElement::setPinController(PinController *pin)
{
    this->pin = pin;
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
void AElement::displayProc()
{
//    this->load();
    this->displayElem();
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

QList<QVariant> const &AElement::getPersistantData() const
{
    return this->persistantData;
}

QList<QVariant> &AElement::getPersistantData()
{
    return this->persistantData;
}

void AElement::sendValueToDevice(int value)
{
    qDebug() << "Sending to device: " << value;
    this->pin->sendValueToDevice(value);
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

void AElement::save()
{

}

void AElement::load()
{

}

void AElement::initSerialization()
{
//    qRegisterMetaTypeStreamOperators<AElement>("AElement");
//    qMetaTypeId<AElement>();

    qRegisterMetaTypeStreamOperators<AElement*>("AElement");
//    qRegisterMetaTypeStreamOperators<ElementSlider*>("ElementSlider");

    qMetaTypeId<AElement*>();               // Teste la validité de la classe Contact
}

QDataStream &operator<<(QDataStream &out, const AElement &value)
{
    qDebug() << "1 [AElement] QDataStream out: pin: " << value.name;

    const_cast<AElement *>(&value)->save();
    out << value.name;
    out << value.getPersistantData();

    return out;
}

QDataStream &operator<<(QDataStream &out, const AElement *&value)
{
    qDebug() << "[2 AElement] QDataStream out: pin: " << value->name;

    const_cast<AElement *>(value)->save();

    out << value->name.toStdString().c_str();
    out << value->getPersistantData();
    return out;
}


QDataStream &operator>>(QDataStream &in, AElement &value)
{
    qDebug() << "3 [AElement >>] QDataStream";

    QList<QVariant> &data = value.getPersistantData();
    QString name;
//    in >> name;
    in >> data;

//    qDebug() << "[AElement] QDataStream in: pin: " << name;
    qDebug() << "           QDataStream in: data: " << data.first();

    return in;
}

QDataStream &operator>>(QDataStream &in, AElement *&value)
{
    qDebug() << "4 [AElement >>] QDataStream";

    QList<QVariant> &data = value->getPersistantData();
//    value = new AElement();
//    in >> value->name;
    in >> data;

//    qDebug() << "[AElement] QDataStream in: pin: " << value->name;
    qDebug() << "           QDataStream in: data: " << data.first();

    return in;
}

//void operator <<(QVariant &data, const AElement *&target)
//{
//    QVariantMap map;
//    map["Name"] << target->name;
//    data << map;
//}

//void operator >>(const QVariant &data, AElement *&target)
//{
//    QVariantMap map;
//    target = new AElement();

//    data >> map;
//    map[ "Name" ] >> target->name;
//}
