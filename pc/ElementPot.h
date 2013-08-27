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

#ifndef ELEMENTPOT_H
#define ELEMENTPOT_H

#include "AElement.h"

class QLineEdit;
class QDial;
class QVBoxLayout;

class ElementPot : public AElement
{
    Q_OBJECT
public:
    ElementPot(QObject *parent = 0);
    ElementPot(const ElementPot &other);
    ~ElementPot();
    virtual void displayElem();
    virtual void save();
    virtual void load();

private:
    virtual void displayConfig();

    QLineEdit *minValue;
    QLineEdit *maxValue;
    QDial *pot;
    QVBoxLayout *displayVBox;

private slots:
    void onApply();

};

#endif // ELEMENTPOT_H
