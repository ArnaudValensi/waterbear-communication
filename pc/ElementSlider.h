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

#ifndef ELEMENTSLIDER_H
#define ELEMENTSLIDER_H

#include "AElement.h"

class QLineEdit;
class QVBoxLayout;
class QSlider;
class QLCDNumber;

class ElementSlider : public AElement
{
    Q_OBJECT
public:
    ElementSlider(PinConfig *pinConfig, QObject *parent = 0);
    ElementSlider(QObject *parent = 0);
    ~ElementSlider();
    virtual void displayElem();

private:
    virtual void displayConfig();

    QLineEdit *minValue;
    QLineEdit *maxValue;
    QVBoxLayout *displayVBox;
    QSlider *slider;
    QLCDNumber *lcd;

private slots:
    void onApply();

};

#endif // ELEMENTSLIDER_H
