#include <QLCDNumber>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QDebug>
#include "ElementPot.h"

ElementSlider::ElementSlider(PinConfig *pinConfig, QString name, QObject *parent)
    : AElement(pinConfig, name, parent)
{
}

// You have to reimplement this function in the child
void ElementSlider::displayConfig()
{
    this->minValue = new QLineEdit();
    this->maxValue = new QLineEdit();
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(minValue);
    hbox->addWidget(maxValue);

    this->setConfigLayout(hbox);
}

// You have to reimplement this function in the child
void ElementSlider::displayElem()
{
    int min;
    int max;

    QVBoxLayout *vbox = new QVBoxLayout();
    QSlider *slider = new QSlider();
    QLCDNumber *lcd = new QLCDNumber();
    bool ok;

    min = this->minValue->text().toInt(&ok);
    if (!ok)
        min = 0;

    max = this->maxValue->text().toInt(&ok);
    if (!ok)
        max = 255;

    qDebug() << "min: " << min;
    qDebug() << "max: " << max;

    slider->setMinimum(min);
    slider->setMaximum(max);

    connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sendValueToArduino(int)));

    vbox->addWidget(lcd);
    vbox->addWidget(slider);
    this->setDisplayLayout(vbox);
}
