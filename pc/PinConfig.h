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

    // For outConfigGroupBox
    QGroupBox *outConfigGroupBox;
    QPushButton *outConfigButton;
    QSlider *outConfigSlider;
    QVBoxLayout *outConfigVbox;

    // For inConfigGroupBox
    QGroupBox *inConfigGroupBox;

    void createOutConfigGroupBox();
    void createInConfigGroupBox();

signals:
    
public slots:
    void displayInConfig();
    void displayOutConfig();

};

#endif // PINCONFIG_H
