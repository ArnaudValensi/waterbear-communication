/* ***** BEGIN LICENSE BLOCK *****
 *
 * This file is part of waterbear-communication.
 *
 * waterbear-communication is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * waterbear-communication is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with waterbear-communication.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef ELEMENTLCD_H
#define ELEMENTLCD_H

#include "AElement.h"

class QLCDNumber;

class ElementLCD : public AElement
{
    Q_OBJECT
public:
    ElementLCD(QObject *parent = 0);
    ElementLCD(ElementLCD const &other);
    virtual ~ElementLCD();
    virtual void displayElem();
    virtual void save();
    virtual void load();

private:
    virtual void displayConfig();

//    QLineEdit *lineEditValue;
//    int value;
    QLCDNumber *lcd;

public slots:
    void sendValue();
    void onApply();

};

#endif // ELEMENTLCD_H
