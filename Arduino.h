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

#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <qextserialport.h>
#include "define_exception.h"

class Arduino : public QObject
{
    Q_OBJECT
public:
    explicit Arduino(QObject *parent = 0);
    ~Arduino();
    void initPort(QString portStr);
    void closePort();
    struct Buffer
    {
        Buffer(char pin, char value) : pin(pin), value(value) {}
        unsigned char pin;
        unsigned char value;
    };

private:
    QextSerialPort *port;
    bool isConnected;
    
signals:
    
public slots:
    void transmitCmd(Arduino::Buffer);
    
};

DEFINE_EXCEPTION(ArduinoError, "ArduinoError")

#endif // ARDUINO_H
