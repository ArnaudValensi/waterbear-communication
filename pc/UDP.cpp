#include "UDP.h"
#include "GuiController.h"
#include <QUdpSocket>

UDP::UDP(QString ip, quint16 port, GuiController *controller, QObject *parent)
    : Communication(parent),
      udpSocket(NULL),
      controller(controller),
      ip(ip),
      port(port)
{
}

UDP::~UDP()
{

}

void UDP::init()
{
    this->udpSocket = new QUdpSocket(this);
//    udpSocket->bind(QHostAddress(ip), 7755);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(onDataAvailable()));
}

void UDP::close()
{
//    if (this->isConnected)
//        port->close();
}

void UDP::onDataAvailable()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        this->controller->displayConsoleMessage(QString(datagram));
    }
}

void UDP::transmitCmd(Communication::Buffer buffer)
{
  qDebug() << "Valeur : " << QString::number(buffer.value) << ", Pin : " << QString::number(buffer.pin);
  if (!this->udpSocket)
  {
      qDebug() << "Error: Not connected to device";
      return;
  }
  this->udpSocket->writeDatagram((char *) &buffer, sizeof(buffer),
                                 this->ip, this->port);
  qDebug() << "Sent";
}
