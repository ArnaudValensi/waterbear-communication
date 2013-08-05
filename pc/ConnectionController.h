#ifndef CONNECTIONCONTROLLER_H
#define CONNECTIONCONTROLLER_H

#include <QDialog>
#include "Communication.h"

namespace Ui {
class DialogConnection;
}

class ConnectionController : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionController(QWidget *parent = 0);
    qint16 getIpPort() const;
    QString getIp() const;
    QString getSerialPort() const;

private:
    Ui::DialogConnection *ui;
    qint16 ipPort;
    QString ip;
    QString serialPort;

private slots:
    void on_pushButtonConnect_clicked();

signals:
    void connect(Communication::Type);

};

#endif // CONNECTIONCONTROLLER_H
