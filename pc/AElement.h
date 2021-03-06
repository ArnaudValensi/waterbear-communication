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

#ifndef AELEMENT_H
#define AELEMENT_H

#include <QObject>
#include <QRadioButton>
#include <QLineEdit>
#include <QLayout>
#include <QVariant>
#include <QDataStream>
#include <QList>
#include <QVariant>


class PinController;
class QDialog;
class QLineEdit;

// TODO: put the virtual member functions in pure.
class AElement : public QObject
{
    Q_OBJECT
public:
    enum TransfertType { IN = 0, OUT };

    // Deprecated
//    explicit AElement(PinConfig *pinConfig, QString name, TransfertType io, QObject *parent = 0);
    explicit AElement(QString name = "Unknown", TransfertType io = OUT, QObject *parent = 0);
    AElement(AElement const &other);
    virtual ~AElement();
    void setPinController(PinController *pin);
    void closeConfigWindow();
    virtual void displayElem();
    virtual void displayConfig();
    AElement::TransfertType getTransfertType();
    QString getName() const;
    QRadioButton *getRadioButton() const;
    QLayout *getDisplayLayout() const;
    QLayout *getConfigLayout() const;
    const QList<QVariant> &getPersistantData() const;
    QList<QVariant> &getPersistantData();
    static void initSerialization();
    virtual void load();
private:

    //PinConfig *pinConfig;
    QString name;
    QRadioButton *radioButton;
    TransfertType transfertType;
    QLayout *displayLayout;
    QLayout *configLayout;
    QDialog *configWindow;
    PinController *pin;
    QLineEdit *lineEditPin;
    friend QDataStream &operator<<(QDataStream &out, const AElement *&value);
    friend QDataStream &operator>>(QDataStream &in, AElement *&value);
    friend QDataStream &operator<<(QDataStream &out, const AElement &value);
    friend QDataStream &operator>>(QDataStream &in, AElement &value);

//    friend QDataStream &operator>>(QDataStream &in, AElement *&value);
//    friend void operator <<(QVariant &data, const AElement *&target);
//    friend void operator >>(const QVariant &data, AElement *&target);
protected:
    QList<QVariant> persistantData;
    void setConfigLayout(QLayout *layout);
    void setDisplayLayout(QLayout *layout);
    virtual void onApply();
    virtual void save();

public slots:
    void displayProc();
    void sendValueToDevice(int value = 0);
    void openConfigWindow();
    void onApplyProc();


};

//Q_DECLARE_METATYPE(AElement)
//QDataStream &operator<<(QDataStream &out, const AElement &value);
//QDataStream &operator>>(QDataStream &in, AElement &value);
Q_DECLARE_METATYPE(AElement*)
QDataStream &operator<<(QDataStream &out, const AElement *&value);
QDataStream &operator>>(QDataStream &in, AElement *&value);
QDataStream &operator>>(QDataStream &in, AElement &value);

//void operator <<(QVariant &data, const AElement *&target);
//void operator >>(const QVariant &data, AElement *&target);

#endif // AELEMENT_H
