#include "Gui.h"
#include "ui_Gui.h"
#include "PinController.h"


Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    for(int i = 0; i < 10; ++i)
        this->addPinControl(i);
}

Gui::~Gui()
{
    while (!pinControllerList.isEmpty())
        delete pinControllerList.takeFirst();
    delete ui;
}

void Gui::addPinControl(quint8 pinNumber)
{
    PinController *pin = new PinController(this, pinNumber);

    pinControllerList.push_back(pin);
}

void Gui::addToTab1Layout(QWidget *widget)\
{
    this->ui->tab1Layout->addWidget(widget);
}
