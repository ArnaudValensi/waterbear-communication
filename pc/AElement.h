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

#ifndef AELEMENT_H
#define AELEMENT_H

#include <QObject>
#include <QRadioButton>
#include <QLineEdit>
#include <QLayout>

class PinConfig;

class AElement : public QObject
{
    Q_OBJECT
public:
    enum TransfertType { IN = 0, OUT };

    // Deprecated
    explicit AElement(PinConfig *pinConfig, QString name, TransfertType io, QObject *parent = 0);
    explicit AElement(QString name, TransfertType io, QObject *parent = 0);
    virtual ~AElement();
    QString getName() const;
    QRadioButton *getRadioButton() const;
    virtual void displayElem();
    AElement::TransfertType getTransfertType();
    QLayout *getDisplayLayout() const;

private:
    virtual void displayConfig();

    PinConfig *pinConfig;
    QString name;
    QRadioButton *radioButton;
    TransfertType transfertType;
    QLayout *displayLayout;

protected:
    void setConfigLayout(QLayout *layout);
    void setDisplayLayout(QLayout *layout);

public slots:
    void displayOut();
    void sendValueToArduino(int value = 0);

};

#endif // AELEMENT_H
