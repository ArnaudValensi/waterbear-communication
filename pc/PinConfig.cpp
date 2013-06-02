#include "PinConfig.h"
#include "GuiController.h"
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>

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
    this->buttonApply = new QPushButton("Apply");


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
    this->vbox->addWidget(this->buttonApply);

    this->buttonApply->hide();
    this->subConfigGroupBox->hide();
    vbox->addStretch();
    this->groupBox->setLayout(vbox);
    this->ui->addToTab2Layout(this->groupBox);

    QObject::connect(radioIn, SIGNAL(clicked(bool)), this, SLOT(displayInConfig()));
    QObject::connect(radioOut, SIGNAL(clicked(bool)), this, SLOT(displayOutConfig()));
    QObject::connect(buttonApply, SIGNAL(clicked(bool)), this, SLOT(apply()));
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
    this->subConfigGroupBox->hide();
    this->outConfigGroupBox->hide();
    this->inConfigGroupBox->show();
    this->clearOutConfig();
    this->buttonApply->hide();
}

void PinConfig::displayOutConfig()
{
    this->subConfigGroupBox->hide();
    this->inConfigGroupBox->hide();
    this->outConfigGroupBox->show();
    this->clearOutConfig();
    this->buttonApply->hide();
}

//--------------------------------------------------------------
// Out options
void PinConfig::displayOutSliderConfig()
{
    this->subConfigGroupBox->show();

    QLineEdit *minValue = new QLineEdit();
    QLineEdit *maxValue = new QLineEdit();
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(minValue);
    hbox->addWidget(maxValue);

    this->clearOutConfig();
    this->subConfigGroupBox->setLayout(hbox);
    this->buttonApply->show();
}

void PinConfig::displayOutPotConfig()
{
    this->subConfigGroupBox->show();

    QLineEdit *minValue = new QLineEdit();
    //QLineEdit *maxValue = new QLineEdit();
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->addWidget(minValue);
    //hbox->addWidget(maxValue);

    this->clearOutConfig();
    this->subConfigGroupBox->setLayout(hbox);
    this->buttonApply->show();
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

// Get the widget in the last group box at the position 'pos'
QWidget *PinConfig::outWidgetAt(int pos)
{
    QLayout *groupBoxLayout = this->subConfigGroupBox->layout();
    if (!groupBoxLayout)
        return NULL;
    QLayoutItem *layoutItem = groupBoxLayout->itemAt(pos);
    if (!layoutItem)
        return NULL;
    return layoutItem->widget();
}

PinController *PinConfig::createPinController(int pin)
{
    this->pinController = ui->addPinControl(pin);
    return this->pinController;
}

void PinConfig::setLayout(QLayout *layout)
{
    this->pinController->setLayout(layout);
}


//--------------------------------------------------------------
// Apply
void PinConfig::apply()
{
    qDebug() << "apply";
    QString pinStr = this->pinNumber->text();
    bool ok;
    this->pin = pinStr.toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this->ui, "Error", "Pin number is not set.");
        return;
    }
    this->createPinController(this->pin);

    if (this->radioOut->isChecked())
    {
        if (this->radioOutSlider->isChecked())
        {
            this->applyOutSlider();
        }
        else if (this->radioOutPot->isChecked())
        {

        }
    }
    else if (this->radioIn->isChecked())
    {

    }
}

void PinConfig::applyOutSlider()
{
    //this->pin
    int min;
    int max;

    // TODO: Exception if null
    QLineEdit *inputTextMin = dynamic_cast<QLineEdit *>(this->outWidgetAt(0));
    QLineEdit *inputTextMax = dynamic_cast<QLineEdit *>(this->outWidgetAt(1));
    if (inputTextMin && inputTextMax)
    {
        QVBoxLayout *vbox = new QVBoxLayout();
        QSlider *slider = new QSlider();
        QLCDNumber *lcd = new QLCDNumber();
        bool ok;

        min = inputTextMin->text().toInt(&ok);
        if (!ok)
            min = 0;

        max = inputTextMax->text().toInt(&ok);
        if (!ok)
            max = 255;

        qDebug() << "min: " << min;
        qDebug() << "max: " << max;

        slider->setMinimum(min);
        slider->setMaximum(max);

        connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));

        vbox->addWidget(lcd);
        vbox->addWidget(slider);
        this->setLayout(vbox);
    }
}
