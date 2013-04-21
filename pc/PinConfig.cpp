#include <QVBoxLayout>
#include "PinConfig.h"
#include "GuiController.h"

PinConfig::PinConfig(GuiController *ui, QObject *parent) :
    QObject(parent),
    ui(ui)
{
    this->groupBox = new QGroupBox();
    this->pinNumber = new QLineEdit();

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(this->pinNumber);
    groupBox->setLayout(vbox);

    this->ui->addToTab2Layout(this->groupBox);
}
