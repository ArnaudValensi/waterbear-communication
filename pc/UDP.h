#ifndef UDP_H
#define UDP_H

#include <Communication.h>
#include "QHostAddress"

class QUdpSocket;
class GuiController;

class UDP : public Communication
{
    Q_OBJECT
public:
    explicit UDP(QString ip, quint16 port, GuiController *controller, QObject *parent = 0);
    ~UDP();
    virtual void init();
    virtual void close();

private:
    QUdpSocket *udpSocket;
    GuiController *controller;
    QHostAddress ip;
    quint16 port;

signals:
    
public slots:
    virtual void transmitCmd(Communication::Buffer);
    void onDataAvailable();

};

#endif // UDP_H
