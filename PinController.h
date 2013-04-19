#ifndef PINCONTROLLER_H
#define PINCONTROLLER_H

#include <QObject>
#include <QGroupBox>
#include <QSlider>
#include <QLineEdit>
#include <QLCDNumber>
#include "Gui.h"

class Gui;

class PinController : public QObject
{
    Q_OBJECT
public:
    explicit PinController(Gui *ui, quint8 pinNumber, QObject *parent = 0);

private:
    static quint8 const defaultMin = 0;
    static quint8 const defaultMax = 255;
    Gui *ui;
    QGroupBox *groupBox;
    QSlider *vertSlider;
    QLineEdit *maxValue;
    QLineEdit *minValue;
    QLCDNumber *lcd;
    
signals:
    
public slots:
    void updateSliderRange();
    
};

#endif // PINCONTROLLER_H
