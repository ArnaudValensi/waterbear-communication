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
