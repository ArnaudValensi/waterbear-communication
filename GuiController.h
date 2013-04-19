#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "PinController.h"
#include "Arduino.h"

namespace Ui {
class Gui;
}

class PinController;

class GuiController : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GuiController(QWidget *parent = 0);
    ~GuiController();
    void addToTab1Layout(QWidget *widget);
    Arduino *getArduino();
    
private:
    Ui::Gui *ui;
    QList<PinController *> pinControllerList;
    Arduino arduino;

    void addPinControl(quint8 pinNumber);

private slots:
    void on_pushButtonConnect_clicked();

};

#endif // GUI_H
