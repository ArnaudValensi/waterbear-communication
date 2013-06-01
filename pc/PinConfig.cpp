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

//    this->outConfigGroupBox = new QGroupBox();
//    this->outConfigButton = new QPushButton("test");
//    this->outConfigSlider = new QSlider();
//    this->outConfigVbox = new QVBoxLayout();
//    this->outConfigGroupBox->setLayout(this->outConfigVbox);
//    this->outConfigVbox->addWidget(this->outConfigButton);
//    this->outConfigVbox->addWidget(this->outConfigSlider);


    radioInOutGroup->addButton(this->radioIn);
    radioInOutGroup->addButton(this->radioOut);

    this->radioIn->setChecked(true);
    this->vbox->addWidget(this->pinNumber);
    this->vbox->addWidget(this->radioIn);
    this->vbox->addWidget(this->radioOut);
//    this->vbox->addWidget(this->outConfigButton);
//    this->vbox->addWidget(this->outConfigGroupBox);

    vbox->addStretch();
    this->groupBox->setLayout(vbox);
    this->ui->addToTab2Layout(this->groupBox);

//    this->groupBox->setTitle("Pin ?");

//    this->radioOut->setChecked(false);

}

void PinConfig::displayInConfig()
{

}

void PinConfig::displayOutConfig()
{

}
