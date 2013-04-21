#include "PinConfig.h"
#include "GuiController.h"
#include <QDebug>

PinConfig::PinConfig(GuiController *ui, QObject *parent) :
    QObject(parent),
    ui(ui)
{
    this->groupBox = new QGroupBox("Pin *");
    this->vbox = new QVBoxLayout();
    this->pinNumber = new QLineEdit();
    this->radioIn = new QRadioButton("In");
    this->radioOut = new QRadioButton("Out");
    this->radioInOutGroup = new QButtonGroup();


    radioInOutGroup->addButton(this->radioIn);
    radioInOutGroup->addButton(this->radioOut);

    this->vbox->addWidget(this->pinNumber);
    this->vbox->addWidget(this->radioIn);
    this->vbox->addWidget(this->radioOut);

    vbox->addStretch();
    this->groupBox->setLayout(vbox);
    qDebug() << "la";
    this->ui->addToTab2Layout(this->groupBox);
//    qDebug() << "laddd";

//    this->groupBox->setTitle("Pin ?");

    this->radioIn->setChecked(true);
//    this->radioOut->setChecked(false);

}
