#include <QMessageBox>
#include "GuiController.h"
#include "ui_Gui.h"
#include "PinController.h"


GuiController::GuiController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    for(int i = 0; i < 10; ++i)
        this->addPinControl(i);
}

GuiController::~GuiController()
{
    while (!pinControllerList.isEmpty())
        delete pinControllerList.takeFirst();
    delete ui;
}

void GuiController::addPinControl(quint8 pinNumber)
{
    PinController *pin = new PinController(this, pinNumber);

    pinControllerList.push_back(pin);
}

void GuiController::addToTab1Layout(QWidget *widget)\
{
    this->ui->tab1Layout->addWidget(widget);
}

void GuiController::on_pushButtonConnect_clicked()
{
    try
    {
        this->arduino.initPort(ui->lineEditPort->text());
        QMessageBox::information(this, "Connected", "Connected to the device.");
    }
    catch (ArduinoError& e)
    {
        QMessageBox::warning(this, "Arduino", e.what());
    }
}

Arduino *GuiController::getArduino()
{
    return &this->arduino;
}
