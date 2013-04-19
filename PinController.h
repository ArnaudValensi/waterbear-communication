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

// TODO: change ui bu controller.

#ifndef PINCONTROLLER_H
#define PINCONTROLLER_H

#include <QObject>
#include <QGroupBox>
#include <QSlider>
#include <QLineEdit>
#include <QLCDNumber>
#include "GuiController.h"
#include "Arduino.h"

class GuiController;

class PinController : public QObject
{
    Q_OBJECT
public:
    explicit PinController(GuiController *ui, quint8 pinNumber, QObject *parent = 0);

private:
    static quint8 const defaultMin = 0;
    static quint8 const defaultMax = 255;
    quint8 pinNumber;
    GuiController *ui;
    QGroupBox *groupBox;
    QSlider *vertSlider;
    QLineEdit *maxValue;
    QLineEdit *minValue;
    QLCDNumber *lcd;
        
public slots:
    void updateSliderRange();
    void sendValueToArduino(int value);

signals:
    void sliderValueChanged(Arduino::Buffer);
    
};

#endif // PINCONTROLLER_H
