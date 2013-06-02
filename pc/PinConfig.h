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

class PinConfig : public QObject
{
    Q_OBJECT
public:
    explicit PinConfig(GuiController *ui, QObject *parent = 0);

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

    // For outConfigGroupBox
    QGroupBox *outConfigGroupBox;
    QVBoxLayout *outConfigVbox;    
    QRadioButton *radioOutSlider;
    QRadioButton *radioOutPot;

    // For inConfigGroupBox
    QGroupBox *inConfigGroupBox;

    QGroupBox *subConfigGroupBox;

    void createOutConfigGroupBox();
    void createInConfigGroupBox();
    void clearOutConfig();

signals:
    
public slots:
    void displayInConfig();
    void displayOutConfig();

    void displayOutSliderConfig();
    void displayOutPotConfig();

};

#endif // PINCONFIG_H
