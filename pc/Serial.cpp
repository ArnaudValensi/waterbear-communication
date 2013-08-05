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

#include <QMessageBox>
#include <QDebug>
#include "Serial.h"
#include "GuiController.h"

Serial::Serial(GuiController *controller, QObject *parent) :
    Communication(parent),
    port(NULL),
    isConnected(false),
    controller(controller)
{
}

Serial::~Serial()
{
    if (this->isConnected)
        port->close(); //we close the port at the end of the program
}

void Serial::init(QString portStr)
{
    if (this->isConnected)
        port->close();

    port = new QextSerialPort(portStr); //we create the port

    connect(port, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));

    port->open(QIODevice::ReadWrite | QIODevice::Unbuffered); //we open the port
    if(!port->isOpen())
        throw SerialError("Unable to open the port!");

    //we set the port properties
    port->setBaudRate(BAUD9600);//modify the port settings on your own
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);

    this->isConnected = true;
}

void Serial::close()
{
    if (this->isConnected)
        port->close();
}

void Serial::transmitCmd(Communication::Buffer buffer)
{
  qDebug() << "Valeur : " << QString::number(buffer.value) << ", Pin : " << QString::number(buffer.pin);
  if (!this->isConnected)
  {
      qDebug() << "Error: Not connected to serial device";
      return;
  }
  port->write((char *) &buffer, sizeof(buffer));
  qDebug() << "Sent";
}

void Serial::onDataAvailable()
{
    QByteArray data = port->readAll();

    this->controller->displayConsoleMessage(QString(data));
}
