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

#include "PinController.h"
#include "AElement.h"
#include "ElementSlider.h"

#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QDialog>
#include <QMetaType>

PinController::PinController(GuiController *ui, quint8 pinNumber, QWidget *parent)
    : QGroupBox(parent),
      pinNumber(pinNumber),
      ui(ui)
{
    qDebug() << "PinController Constructor";

    this->elem = NULL;
    this->setFixedWidth(this->fixedWidth);
    if (this->ui)
    {
        this->ui->addToTab1Layout(this);

        Serial *serial = ui->getSerial();
        QObject::connect(this, SIGNAL(valueChanged(Communication::Buffer)), serial, SLOT(transmitCmd(Communication::Buffer)));
    }
    this->setTitle(QString("Pin %1").arg(this->pinNumber));

    this->createActions();

    this->resizing = false;
//    this->sizeGrip = new QSizeGrip(this);
}

PinController::PinController(PinController const &other)
    : QGroupBox()
{
    qDebug() << "PinController Copy Constructor";

    this->elem = NULL;
    this->ui = other.ui;
    this->pinNumber = other.pinNumber;
    if (other.elem)
    {
        qDebug() << "PinController Copy elem: " << other.elem->getName();

        this->elem = other.elem;
    }
    else
        qDebug() << "PinController Copy pas elem";


    this->setFixedWidth(this->fixedWidth);
    if (this->ui)
    {
        this->ui->addToTab1Layout(this);

        Serial *serial = ui->getSerial();
        QObject::connect(this, SIGNAL(valueChanged(Communication::Buffer)), serial, SLOT(transmitCmd(Communication::Buffer)));
    }
    this->setTitle(QString("Pin %1").arg(this->pinNumber));

    this->createActions();
}

PinController::~PinController()
{

}

void PinController::setUi(GuiController *ui)
{
    if (!ui)
        return;

    this->ui = ui;
    if (this->elem == NULL)
        qDebug() << "Error: this->elem == NULL";
    else
    {
        this->addElement(this->elem);
        this->elem->load();
    }
    this->ui->addToTab1Layout(this);
    this->updateGeometry();

    Serial *serial = ui->getSerial();
    QObject::connect(this, SIGNAL(valueChanged(Communication::Buffer)), serial, SLOT(transmitCmd(Communication::Buffer)));
}

void PinController::sendValueToDevice(int value)
{
    Communication::Buffer buffer(this->pinNumber, value);
    emit valueChanged(buffer);
}

int PinController::getPinNumber() const
{
    return this->pinNumber;
}

void PinController::addElement(AElement *elem)
{
    this->elem = elem;
    elem->displayProc();
    // Deprecated
    elem->displayConfig();
    this->setLayout(elem->getDisplayLayout());
    elem->setPinController(this);
}

void PinController::mousePressEvent(QMouseEvent *event)
{
    offset = event->pos();
}

void PinController::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if (this->resizing)
        {
            QPoint p = event->pos();
            QSize newSize = QSize(p.rx(), p.ry());
            this->resize(newSize);
        }
        else
            this->move(this->mapToParent(event->pos() - offset));
    }

//    qDebug() << "pos: " << event->pos();

    if (this->size().width() - event->pos().rx() < 8 &&
        this->size().height() - event->pos().ry() < 8)
    {
        qDebug() << "Corner enter";
        this->setCursor(Qt::SizeFDiagCursor);
        this->resizing = true;

    }
    // TODO: not very good.
    else
    {
//        qDebug() << "Corner leave";
        this->setCursor(Qt::SizeAllCursor);
//        this->resizing = false;
    }
}

void PinController::mouseReleaseEvent(QMouseEvent *event)
{
    // TODO: protect against the right click

    if (!this->ui)
        return;

    if (this->ui->isGridAuto())
    {
        // Strategie auto
        QHBoxLayout *layout = this->ui->getTab1Layout();
        QList<PinController *> *pinControllerList = this->ui->getPinControllerList();

        int index = pinControllerList->indexOf(this);
        int mouseX = this->mapToParent(event->pos()).x();
        int newIndex = mouseX / PinController::fixedWidth;
        int listSize = pinControllerList->size();

        if (newIndex > listSize)
            newIndex = listSize;

        PinController *pinController = pinControllerList->at(index);
        pinControllerList->removeAt(index);
        pinControllerList->insert(newIndex, pinController);

        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != NULL)
            layout->removeItem(item);

        foreach (PinController *p, *pinControllerList) {
            layout->addWidget(p);
        }

        this->updateGeometry();
    }
//    else
//    {
//        // Strategie manual
//        return;
//    }
//    this->setCursor(Qt::ArrowCursor);

//    if ()
//    emit leaveEvent();
}

void PinController::enterEvent(QEvent *event)
{
    qDebug() << "Enter event";

    (void) event;

    this->setCursor(Qt::SizeAllCursor);
    this->setMouseTracking(true);
}

void PinController::leaveEvent(QEvent * event)
{
    qDebug() << "Leave event";

    (void) event;

    this->setMouseTracking(false);
    this->resizing = false;
}

void PinController::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(this->editAct);
    menu.exec(event->globalPos());
}

void PinController::createActions()
{
    this->editAct = new QAction(tr("&Edit"), this);
    this->editAct->setShortcuts(QKeySequence::Preferences);
    this->editAct->setStatusTip(tr("Edit the element"));
    connect(this->editAct, SIGNAL(triggered()), this, SLOT(editElement()));
}

void PinController::editElement()
{
    qDebug() << "Edit";

    this->elem->openConfigWindow();
}

void PinController::print()
{
    qDebug() << "--[PinController] pinNum" << this->pinNumber;
    if (this->elem)
        qDebug() << "--[Elem]          name  " << this->elem->getName();
//    qDebug() << "--[PinController] test2" << this->test2;
}

void PinController::initSerialization()
{
    qRegisterMetaTypeStreamOperators<PinController>("PinController");

    qDebug() << "PinController ID: " << qMetaTypeId<PinController>();
//    qDebug() << "ElementSlider ID: " << qMetaTypeId<ElementSlider>();
//    qMetaTypeId<PinController*>();               // Teste la validité de la classe Contact
//    qMetaTypeId<QRect>();               // Teste la validité de la classe Contact
}

QDataStream &operator<<(QDataStream &out, const PinController &value)
{
    qDebug() << "[PinController <<] pin: " << value.pinNumber;
//    qDebug() << "                   value.test: " << value.test2;

//    qDebug() << "[PinController <<] ElementSlider ID: " << qMetaTypeId<ElementSlider>();


    out << value.pinNumber;
    out << *value.elem;

    return out;
}

QDataStream &operator>>(QDataStream &in, PinController &value)
{
    qDebug() << "==================";

    QString elemName;

    in >> value.pinNumber;
    in >> elemName;

//    ElementSlider *elem = 0;
//    AElement *elem = 0;

    int elemId = QMetaType::type((elemName + "*").toStdString().c_str());
    if (elemId != QMetaType::UnknownType)
    {
        qDebug() << "elemId: " << elemId;
        value.elem = ElementFactorySingleton::getInstance()->createById(elemId);
        if (!value.elem)
            qDebug() << "Error: elem NULL";

        in >> value.elem;
    }
    else
        qDebug() << "QMetaType unknown";

    qDebug() << "[PinController >>] QDataStream in: pin: " << value.pinNumber;
//    qDebug() << "                   value.test: " << value.test2;
    qDebug() << "                   elemName: " << value.elem->getName();
    qDebug() << "                   elemId: " << elemId;

    return in;
}

//QDataStream &operator<<(QDataStream &out, const QRect *value)
//{
//    qDebug() << "[QRect <<] << " << *value;

//    out << *value;

//    return out;
//}

//QDataStream &operator<<(QDataStream &out, const QRect *&value)
//{
//    qDebug() << "[QRect <<] << " << *value;

//    out << *value;

//    return out;
//}

//QDataStream &operator>>(QDataStream &in, QRect *&value)
//{
//    value = new QRect();

//    in >> value;

//    qDebug() << "[QRect >>] >> " << *value;

//    return in;
//}

//QDataStream &operator<<(QDataStream &out, const QRect &value)
//{
//    qDebug() << "[QRect <<] << " << value;

//    out << value;

//    return out;
//}

//QDataStream &operator>>(QDataStream &in, QRect &value)
//{
////    value = new QRect();

//    in >> value;

//    qDebug() << "[QRect >>] >> " << value;

//    return in;
//}
