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
