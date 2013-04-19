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

#include <QMessageBox>
#include <QDebug>
#include "Arduino.h"

Arduino::Arduino(QObject *parent) :
    QObject(parent),
    port(NULL),
    isConnected(false)
{
}

Arduino::~Arduino()
{
    if (this->isConnected)
        port->close(); //we close the port at the end of the program
}

void Arduino::initPort(QString portStr)
{
    if (this->isConnected)
        port->close();

    port = new QextSerialPort(portStr); //we create the port

    port->open(QIODevice::ReadWrite | QIODevice::Unbuffered); //we open the port
    if(!port->isOpen())
        throw ArduinoError("Unable to open the port!");

    //we set the port properties
    port->setBaudRate(BAUD9600);//modify the port settings on your own
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);

    this->isConnected = true;
}

void Arduino::closePort()
{
    if (this->isConnected)
        port->close();
}

void Arduino::transmitCmd(Arduino::Buffer buffer)
{
  if (!this->isConnected)
  {
      qDebug() << "Error: Not connected to Arduino";
      return;
  }
  port->write((char *) &buffer, sizeof(buffer));
  qDebug() << "Valeur : " << QString::number(buffer.value) << ", Pin : " << QString::number(buffer.pin);
}
