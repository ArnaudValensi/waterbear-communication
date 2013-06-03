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
#include <QMap>
//#include "PinController.h"

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
    //QWidget *outConfig;
    QPushButton *buttonApply;
    //QList<AElement *> elementList;
    QList<AElement *> elementList;

    // For outConfigGroupBox
    QGroupBox *outConfigGroupBox;
    QVBoxLayout *outConfigVbox;    
//    QRadioButton *radioOutSlider;
//    QRadioButton *radioOutPot;

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

    void displayOutSliderConfig();
    void displayOutPotConfig();

    void apply();
    void sendValueToArduino(int value);

    // Dprecated
    QGroupBox *getSubConfigGroupBox();
};

#endif // PINCONFIG_H
