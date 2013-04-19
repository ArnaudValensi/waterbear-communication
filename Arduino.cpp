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
        throw ArduinoError("Impossible to open the port!");

    //we set the port properties
    port->setBaudRate(BAUD9600);//modify the port settings on your own
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
}

void Arduino::closePort()
{
    if (this->isConnected)
        port->close();
}

//void Arduino::on_pushButtonConnect_clicked()
//{
//    init_port(ui->lineEditPort->text());
//}

void Arduino::transmitCmd(int value)
{
  if(value < 0 || value > 255)return; //if the value is not between 0 and 255 no transmission

  char buf = value;
  port->write(&buf, 1);
  qDebug() << "Valeur : " << value;
}
