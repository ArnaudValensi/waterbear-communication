#ifndef ELEMENTPOT_H
#define ELEMENTPOT_H

#include "AElement.h"

class ElementSlider : public AElement
{
public:
    ElementSlider(PinConfig *pinConfig, QString name, QObject *parent = 0);
    virtual void displayElem();

private:
    virtual void displayConfig();

    QLineEdit *minValue;
    QLineEdit *maxValue;

};

#endif // ELEMENTPOT_H
