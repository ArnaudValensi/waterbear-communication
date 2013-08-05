#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>

class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = 0);
    virtual void init() = 0;
    virtual void close() = 0;
    struct Buffer
    {
        Buffer(char pin, char value) : pin(pin), value(value) {}
        unsigned char pin;
        unsigned char value;
    } __attribute__((__packed__));

signals:
    
public slots:
    virtual void transmitCmd(Communication::Buffer) = 0;
    //void onDataAvailable();
};

#endif // COMMUNICATION_H
