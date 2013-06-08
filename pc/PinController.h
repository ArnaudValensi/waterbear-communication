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

// TODO: change ui by controller.

#ifndef PINCONTROLLER_H
#define PINCONTROLLER_H

#include <QObject>
#include <QGroupBox>
#include <QVariant>
#include <QDataStream>
#include <QRect>
#include "GuiController.h"
#include "Arduino.h"
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
//    ElementFactory *getElementFactory();

//    QRect test;
//    QString test2;

private:
    static int const fixedWidth = 130;
    static quint8 const defaultMin = 0;
    static quint8 const defaultMax = 255;
    quint8 pinNumber;
    GuiController *ui;
    //QGroupBox *groupBox;
    QPoint offset;
    QAction *editAct;
    AElement *elem;

    void createActions();
    friend QDataStream &operator<<(QDataStream &out, const PinController &value);
    friend QDataStream &operator>>(QDataStream &in, PinController &value);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent * event);

public slots:
    void sendValueToArduino(int value);
    void editElement();

signals:
    void valueChanged(Arduino::Buffer);
    
};

Q_DECLARE_METATYPE(PinController)
QDataStream &operator<<(QDataStream &out, const PinController &value);
QDataStream &operator>>(QDataStream &in, PinController &value);

#endif // PINCONTROLLER_H
