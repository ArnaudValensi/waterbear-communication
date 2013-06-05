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
#include "GuiController.h"
#include "Arduino.h"
#include "AElement.h"

class GuiController;

class PinController : public QGroupBox
{
    Q_OBJECT
public:
    explicit PinController(GuiController *ui, quint8 pinNumber, QWidget *parent = 0);
    int getPinNumber() const;
    void addElement(AElement *elem);

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

#endif // PINCONTROLLER_H
