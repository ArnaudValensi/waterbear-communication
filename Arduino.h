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

private:
    QextSerialPort *port;
    bool isConnected;
    
signals:
    
public slots:
    void transmitCmd(int value);
    
};

DEFINE_EXCEPTION(ArduinoError, "ArduinoError")

#endif // ARDUINO_H
