#include "ConnectionController.h"
#include "ui_Connection.h"
#include <QMessageBox>

ConnectionController::ConnectionController(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DialogConnection)
{
    ui->setupUi(this);
}

void ConnectionController::on_pushButtonConnect_clicked()
{
    if (this->ui->radioButtonSerial->isChecked())
    {
        this->serialPort = this->ui->lineEditEditPort->text();

        if (this->serialPort.isEmpty())
        {
            QMessageBox::warning(this, "Error", "You must give a serial port");
            return;
        }

        emit connect(Communication::SERIAL);
    }
    else if (this->ui->radioButtonUDP->isChecked())
    {
        this->ip = this->ui->lineEditIP->text();
        QString port = this->ui->lineEditUDPPort->text();

        if (ip.isEmpty())
        {
            QMessageBox::warning(this, "Error", "You must give an IP address");
            return;
        }
        if (port.isEmpty())
        {
            QMessageBox::warning(this, "Error", "You must give a port");
            return;
        }

        bool ok;
        int intPort = port.toInt(&ok);

        if (!ok)
        {
            QMessageBox::warning(this, "Error", "IP port must be a number");
            return;
        }

        if (intPort < 0 || intPort > 65535)
        {
            QMessageBox::warning(this, "Error", "Port must be between 0 and 65535");
            return;
        }

        this->ipPort = intPort;

        emit connect(Communication::UDP);
    }
}

qint16 ConnectionController::getIpPort() const
{
    return this->ipPort;
}

QString ConnectionController::getIp() const
{
    return this->ip;
}

QString ConnectionController::getSerialPort() const
{
    return this->serialPort;
}
