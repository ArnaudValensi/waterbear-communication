#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "PinController.h"

namespace Ui {
class Gui;
}

class PinController;

class Gui : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();
    void addToTab1Layout(QWidget *widget);
    
private:
    Ui::Gui *ui;
    QList<PinController *> pinControllerList;

    void addPinControl(quint8 pinNumber);
};

#endif // GUI_H
