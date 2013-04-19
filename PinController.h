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
