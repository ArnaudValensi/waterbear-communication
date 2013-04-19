#include <QVBoxLayout>
#include "PinController.h"

PinController::PinController(Gui *ui, quint8 pinNumber, QObject *parent) :
    QObject(parent),
    ui(ui)
{
    this->groupBox = new QGroupBox();
    this->vertSlider = new QSlider(Qt::Vertical);
    this->maxValue = new QLineEdit();
    this->minValue = new QLineEdit();
    this->lcd = new QLCDNumber();

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(maxValue);
    vbox->addWidget(vertSlider);
    vbox->addWidget(minValue);
    vbox->addWidget(lcd);
    //vbox->addStretch(1);
    groupBox->setLayout(vbox);
    this->ui->addToTab1Layout(groupBox);

    groupBox->setTitle(QString("Pin %1").arg(pinNumber));
    maxValue->setText(QString::number(defaultMax));
    minValue->setText(QString::number(defaultMin));
    vertSlider->setRange(defaultMin, defaultMax);
//    maxValue->setMaxLength(3);
//    minValue->setMaxLength(3);
//    QRect maxValueRect = maxValue->geometry();
//    maxValueRect.setWidth(41);
//    maxValue->setGeometry(maxValueRect);

    //connect(vertSlider, &QSlider::valueChanged, lcd, &QLCDNumber::display);
    connect(vertSlider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
    //connect(vertSlider, SIGNAL(valueChanged(int)), this, SLOT(transmitCmd(int)));
    connect(maxValue, SIGNAL(editingFinished()), this, SLOT(updateSliderRange()));
    connect(minValue, SIGNAL(editingFinished()), this, SLOT(updateSliderRange()));
}

void PinController::updateSliderRange()
{
    quint8 max = this->maxValue->text().toUShort();
    quint8 min = this->minValue->text().toUShort();

    vertSlider->setRange(min, max);
}
