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

// TODO: change ui by controller.

#ifndef PINCONTROLLER_H
#define PINCONTROLLER_H

#include <QObject>
#include <QGroupBox>
#include <QVariant>
#include <QDataStream>
#include <QRect>
#include <QSizeGrip>
#include "GuiController.h"
#include "Serial.h"
#include "AElement.h"
#include "ElementFactory.h"

//Q_DECLARE_METATYPE(QRect*)
//QDataStream &operator<<(QDataStream &out, const QRect *&value);
//QDataStream &operator>>(QDataStream &in, QRect *&value);
//QDataStream &operator<<(QDataStream &out, const QRect *value);
//QDataStream &operator<<(QDataStream &out, const QRect &value);
//QDataStream &operator>>(QDataStream &in, QRect &value);

class GuiController;

class PinController : public QGroupBox
{
    Q_OBJECT
public:
    explicit PinController(GuiController *ui = NULL, quint8 pinNumber = 23, QWidget *parent = 0);
    PinController(PinController const &other);
    ~PinController();
    int getPinNumber() const;
    void addElement(AElement *elem);
    void setUi(GuiController *ui);
    void print();
    static void initSerialization();

private:
    static int const fixedWidth = 130;
    static quint8 const defaultMin = 0;
    static quint8 const defaultMax = 255;
    quint8 pinNumber;
    GuiController *ui;
    QPoint offset;
    QAction *editAct;
    AElement *elem;
    bool resizing;
//    QSizeGrip *sizeGrip;

    void createActions();
    friend QDataStream &operator<<(QDataStream &out, const PinController &value);
    friend QDataStream &operator>>(QDataStream &in, PinController &value);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent * event);
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);

public slots:
    void sendValueToDevice(int value);
    void editElement();

signals:
    void valueChanged(Communication::Buffer);
    
};

Q_DECLARE_METATYPE(PinController)
QDataStream &operator<<(QDataStream &out, const PinController &value);
QDataStream &operator>>(QDataStream &in, PinController &value);

#endif // PINCONTROLLER_H
