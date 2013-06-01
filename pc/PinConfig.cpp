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


    this->createOutConfigGroupBox();
    this->createInConfigGroupBox();


    radioInOutGroup->addButton(this->radioIn);
    radioInOutGroup->addButton(this->radioOut);

    this->radioOut->setChecked(true);
    this->inConfigGroupBox->hide();

    this->vbox->addWidget(this->pinNumber);
    this->vbox->addWidget(this->radioIn);
    this->vbox->addWidget(this->radioOut);
//    this->vbox->addWidget(this->outConfigButton);

    this->vbox->addWidget(this->inConfigGroupBox);
    this->vbox->addWidget(this->outConfigGroupBox);

    vbox->addStretch();
    this->groupBox->setLayout(vbox);
    this->ui->addToTab2Layout(this->groupBox);

//    this->groupBox->setTitle("Pin ?");

//    this->radioOut->setChecked(false);

    QObject::connect(radioIn, SIGNAL(clicked(bool)), this, SLOT(displayInConfig()));
    QObject::connect(radioOut, SIGNAL(clicked(bool)), this, SLOT(displayOutConfig()));
}

void PinConfig::createOutConfigGroupBox()
{
    // This is displayed when 'out' is selected in checkbox
    this->outConfigGroupBox = new QGroupBox();
    this->outConfigButton = new QPushButton("test");
    this->outConfigSlider = new QSlider();
    this->outConfigVbox = new QVBoxLayout();
    this->outConfigGroupBox->setLayout(this->outConfigVbox);
    this->outConfigVbox->addWidget(this->outConfigButton);
    this->outConfigVbox->addWidget(this->outConfigSlider);
}

void PinConfig::createInConfigGroupBox()
{
    // This is displayed when 'out' is selected in checkbox
    this->inConfigGroupBox = new QGroupBox();
}

void PinConfig::displayInConfig()
{
    qDebug() << "radioIn clicked";
//    this->vbox->removeWidget(this->outConfigGroupBox);
    this->outConfigGroupBox->hide();
    this->inConfigGroupBox->show();
//    this->vbox->addWidget(this->inConfigGroupBox);
}

void PinConfig::displayOutConfig()
{
    qDebug() << "radioOut clicked";
//    this->vbox->removeWidget(this->inConfigGroupBox);
    this->inConfigGroupBox->hide();
    this->outConfigGroupBox->show();
//    this->vbox->addWidget(this->outConfigGroupBox);
}
