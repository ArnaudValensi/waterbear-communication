//#include <QLCDNumber>
#include <QDebug>
#include "AElement.h"
#include "PinConfig.h"

AElement::AElement(PinConfig *pinConfig, QString name, QObject *parent) :
    QObject(parent)
{
    this->pinConfig = pinConfig;
    this->name = name;

    this->radioButton = new QRadioButton(name);
    QObject::connect(radioButton, SIGNAL(clicked(bool)), this, SLOT(displayOut()));
}

QString AElement::getName() const
{
    return this->name;
}

QRadioButton *AElement::getRadioButton() const
{
    return this->radioButton;
}

void AElement::displayOut()
{
    this->pinConfig->preDisplayConfig();
    this->displayConfig();
    this->pinConfig->postDisplayConfig();
}

void AElement::setConfigLayout(QLayout *layout)
{
    this->pinConfig->setConfigLayout(layout);
}

void AElement::setDisplayLayout(QLayout *layout)
{
    this->pinConfig->setLayout(layout);
}

void AElement::sendValueToArduino(int value)
{
    this->pinConfig->sendValueToArduino(value);
    qDebug() << "Sent to Arduino: " << value;
}

// You have to reimplement this function in the child
void AElement::displayConfig()
{
//    this->minValue = new QLineEdit();
//    this->maxValue = new QLineEdit();
//    QHBoxLayout *hbox = new QHBoxLayout();

//    hbox->addWidget(minValue);
//    hbox->addWidget(maxValue);

//    this->setConfigLayout(hbox);
}

// You have to reimplement this function in the child
void AElement::displayElem()
{
//    int min;
//    int max;

//    QVBoxLayout *vbox = new QVBoxLayout();
//    QSlider *slider = new QSlider();
//    QLCDNumber *lcd = new QLCDNumber();
//    bool ok;

//    min = this->minValue->text().toInt(&ok);
//    if (!ok)
//        min = 0;

//    max = this->maxValue->text().toInt(&ok);
//    if (!ok)
//        max = 255;

//    qDebug() << "min: " << min;
//    qDebug() << "max: " << max;

//    slider->setMinimum(min);
//    slider->setMaximum(max);

//    connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
//    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sendValueToArduino(int)));

//    vbox->addWidget(lcd);
//    vbox->addWidget(slider);
//    this->setDisplayLayout(vbox);
}
