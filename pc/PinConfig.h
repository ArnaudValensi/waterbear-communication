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

#ifndef PINCONFIG_H
#define PINCONFIG_H

#include <QObject>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QSlider>

class GuiController;
class PinController;
class AElement;

class PinConfig : public QObject
{
    Q_OBJECT
public:
    explicit PinConfig(GuiController *ui, QObject *parent = 0);
    void preDisplayConfig();
    void postDisplayConfig();
    void setConfigLayout(QLayout *layout);
    void setLayout(QLayout *layout);

private:
    GuiController *ui;
    QGroupBox *groupBox;
    QLineEdit *pinNumber;
    QRadioButton *radioIn;
    QRadioButton *radioOut;
    QButtonGroup *radioInOutGroup;
    QVBoxLayout *vbox;
    QPushButton *buttonApply;
    QList<AElement *> elementList;

    // For outConfigGroupBox
    QGroupBox *outConfigGroupBox;
    QVBoxLayout *outConfigVbox;    

    // For inConfigGroupBox
    QGroupBox *inConfigGroupBox;
    QGroupBox *subConfigGroupBox;

    int pin;
    PinController *pinController;

    void createOutConfigGroupBox();
    void createInConfigGroupBox();
    void clearOutConfig();
    QWidget *outWidgetAt(int pos);

    void applyOutSlider();
    PinController *createPinController(int pin);

public slots:
    void displayInConfig();
    void displayOutConfig();

    // Dprecated
    void displayOutPotConfig();

    void apply();
    void sendValueToArduino(int value);
};

#endif // PINCONFIG_H
