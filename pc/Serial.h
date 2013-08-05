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

#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <qextserialport.h>
#include "define_exception.h"
#include "Communication.h"

class GuiController;

class Serial : public Communication
{
    Q_OBJECT
public:
    explicit Serial(QString portStr, GuiController *controller, QObject *parent = 0);
    ~Serial();
    virtual void init();
    virtual void close();

private:
    QString portStr;
    QextSerialPort *port;
    bool isConnected;
    GuiController *controller;
    
signals:
    
public slots:
    virtual void transmitCmd(Communication::Buffer);
    void onDataAvailable();
    
};

DEFINE_EXCEPTION(SerialError, "SerialError")

#endif // SERIAL_H
