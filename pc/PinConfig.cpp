#include "PinConfig.h"
#include "GuiController.h"
#include <QDebug>
#include <QLineEdit>

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

    // Sub config
    this->subConfigGroupBox = new QGroupBox();

    radioInOutGroup->addButton(this->radioIn);
    radioInOutGroup->addButton(this->radioOut);

    this->radioOut->setChecked(true);
    this->inConfigGroupBox->hide();

    this->vbox->addWidget(this->pinNumber);
    this->vbox->addWidget(this->radioIn);
    this->vbox->addWidget(this->radioOut);

    this->vbox->addWidget(this->inConfigGroupBox);
    this->vbox->addWidget(this->outConfigGroupBox);
    this->vbox->addWidget(this->subConfigGroupBox);

    vbox->addStretch();
    this->groupBox->setLayout(vbox);
    this->ui->addToTab2Layout(this->groupBox);

    QObject::connect(radioIn, SIGNAL(clicked(bool)), this, SLOT(displayInConfig()));
    QObject::connect(radioOut, SIGNAL(clicked(bool)), this, SLOT(displayOutConfig()));
}

// This is displayed when 'out' is selected in checkbox
void PinConfig::createOutConfigGroupBox()
{
    this->outConfigGroupBox = new QGroupBox();
    this->outConfigVbox = new QVBoxLayout();

    this->radioOutSlider = new QRadioButton("Slider");
    this->radioOutPot = new QRadioButton("Pot");

    this->outConfigGroupBox->setLayout(this->outConfigVbox);
    this->outConfigVbox->addWidget(this->radioOutSlider);
    this->outConfigVbox->addWidget(this->radioOutPot);

    QObject::connect(radioOutSlider, SIGNAL(clicked(bool)), this, SLOT(displayOutSliderConfig()));
    QObject::connect(radioOutPot, SIGNAL(clicked(bool)), this, SLOT(displayOutPotConfig()));
}

void PinConfig::createInConfigGroupBox()
{
    // This is displayed when 'out' is selected in checkbox
    this->inConfigGroupBox = new QGroupBox();
}

//--------------------------------------------------------------
// Display
void PinConfig::displayInConfig()
{
    this->outConfigGroupBox->hide();
    this->inConfigGroupBox->show();
    this->clearOutConfig();
}

void PinConfig::displayOutConfig()
{
    this->inConfigGroupBox->hide();
    this->outConfigGroupBox->show();
    this->clearOutConfig();
}

//--------------------------------------------------------------
// Out options
void PinConfig::displayOutSliderConfig()
{
    QLineEdit *minValue = new QLineEdit();
    QLineEdit *maxValue = new QLineEdit();
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(minValue);
    hbox->addWidget(maxValue);

    this->clearOutConfig();
    this->subConfigGroupBox->setLayout(hbox);
}

void PinConfig::displayOutPotConfig()
{
    QLineEdit *minValue = new QLineEdit();
    //QLineEdit *maxValue = new QLineEdit();
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(minValue);
    //hbox->addWidget(maxValue);

    this->clearOutConfig();
    this->subConfigGroupBox->setLayout(hbox);
}

void PinConfig::clearOutConfig()
{
    QLayout *groupBoxLayout = this->subConfigGroupBox->layout();

    if (!groupBoxLayout)
        return;
    while (!groupBoxLayout->isEmpty())
    {
        QWidget *widget = groupBoxLayout->itemAt(0)->widget();
        groupBoxLayout->removeWidget(widget);
        delete widget;
    }
    delete groupBoxLayout;
}
