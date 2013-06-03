/* ***** BEGIN LICENSE BLOCK *****
 *
 * This file is part of arduino-control-interface.
 *
 * arduino-control-interface is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * arduino-control-interface is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with arduino-control-interface.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ***** END LICENSE BLOCK ***** */

#include <QDebug>
#include <QMessageBox>
#include "PinConfig.h"
#include "GuiController.h"
#include "AElement.h"
#include "ElementSlider.h"
#include "ElementPot.h"
#include "ElementPushButton.h"

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

    AElement *slider = new ElementSlider(this, "Slider");
    AElement *pot = new ElementPot(this, "Pot");
    AElement *button = new ElementPushButton(this, "Button");
    this->elementList.push_back(slider);
    this->elementList.push_back(pot);
    this->elementList.push_back(button);

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
    this->groupBox->setFixedWidth(140);
    this->groupBox->setLayout(vbox);
    this->ui->addToTab2Layout(this->groupBox);

    QObject::connect(radioIn, SIGNAL(clicked(bool)), this, SLOT(displayInConfig()));
    QObject::connect(radioOut, SIGNAL(clicked(bool)), this, SLOT(displayOutConfig()));
    QObject::connect(buttonApply, SIGNAL(clicked(bool)), this, SLOT(apply()));
}

//void PinConfig::createConfigGroupBox()
//{

//}

// This is displayed when 'out' is selected in checkbox
void PinConfig::createOutConfigGroupBox()
{
    this->outConfigGroupBox = new QGroupBox();
    this->outConfigVbox = new QVBoxLayout();
    this->outConfigGroupBox->setLayout(this->outConfigVbox);

    for (int i = 0; i < this->elementList.size(); ++i)
        this->outConfigVbox->addWidget(this->elementList.at(i)->getRadioButton());
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
void PinConfig::preDisplayConfig()
{
    this->subConfigGroupBox->show();
    this->clearOutConfig();
    this->buttonApply->show();
}

void PinConfig::postDisplayConfig()
{

}

void PinConfig::setConfigLayout(QLayout *layout)
{
    this->subConfigGroupBox->setLayout(layout);
}

// Deprecated
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

void PinConfig::sendValueToArduino(int value)
{
    this->pinController->sendValueToArduino(value);
}

//--------------------------------------------------------------
// Apply
void PinConfig::apply()
{
    QString pinStr = this->pinNumber->text();
    bool ok;
    this->pin = pinStr.toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this->ui, "Error", "Pin number is not set.");
        return;
    }
    this->createPinController(this->pin);

    for (int i = 0; i < this->elementList.size(); ++i)
    {
        AElement *elem = this->elementList.at(i);
        if (elem->getRadioButton()->isChecked())
        {
            elem->displayElem();
            return;
        }
    }
}
