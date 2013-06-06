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

#include "PinController.h"
#include "AElement.h"

#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QDialog>

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

        Arduino *arduino = ui->getArduino();
        QObject::connect(this, SIGNAL(valueChanged(Arduino::Buffer)), arduino, SLOT(transmitCmd(Arduino::Buffer)));
    }
    this->setTitle(QString("Pin %1").arg(this->pinNumber));

    this->createActions();
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
        qDebug() << "PinController Copy elem";

        this->elem = other.elem;
    }
    else
        qDebug() << "PinController Copy pas elem";


    this->setFixedWidth(this->fixedWidth);
    if (this->ui)
    {
        this->ui->addToTab1Layout(this);

        Arduino *arduino = ui->getArduino();
        QObject::connect(this, SIGNAL(valueChanged(Arduino::Buffer)), arduino, SLOT(transmitCmd(Arduino::Buffer)));
    }
    this->setTitle(QString("Pin %1").arg(this->pinNumber));

    this->createActions();
}

PinController::~PinController()
{

}

void PinController::sendValueToArduino(int value)
{
    Arduino::Buffer buffer(this->pinNumber, value);
    emit valueChanged(buffer);
}

int PinController::getPinNumber() const
{
    return this->pinNumber;
}

void PinController::addElement(AElement *elem)
{
    this->elem = elem;
    elem->displayOut();
    // Deprecated
    elem->displayConfig();
    this->setLayout(elem->getDisplayLayout());
}

void PinController::mousePressEvent(QMouseEvent *event)
{
    offset = event->pos();
}

void PinController::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(this->mapToParent(event->pos() - offset));
    }
}

void PinController::mouseReleaseEvent(QMouseEvent *event)
{
    // TODO: protect against the right click

    if (!this->ui)
        return;

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

void PinController::contextMenuEvent(QContextMenuEvent * event)
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
    //this->elem->getConfigLayout()->show();

//    QDialog *secondWindow = new QDialog(this);
//    secondWindow->setLayout(this->elem->getConfigLayout());
//    secondWindow->show();
//    secondWindow->activateWindow();
    this->elem->openConfigWindow();
}

void PinController::print()
{
    qDebug() << "[PinController] pinNum" << this->pinNumber;
    if (this->elem)
        qDebug() << "[Elem]          name  " << this->elem->getName();
}

void PinController::initSerialization()
{
    qRegisterMetaTypeStreamOperators<PinController>("PinController");

    qMetaTypeId<PinController>();               // Teste la validité de la classe Contact
}

QDataStream &operator<<(QDataStream &out, const PinController &value)
{
    qDebug() << "[PinController] QDataStream out: pin: " << value.pinNumber;

    out << value.pinNumber
        << value.elem;

    return out;
}

QDataStream &operator>>(QDataStream &in, PinController &value)
{
    in >> value.pinNumber
       >> value.elem;

    qDebug() << "[PinController] QDataStream in: pin: " << value.pinNumber;

    return in;
}
