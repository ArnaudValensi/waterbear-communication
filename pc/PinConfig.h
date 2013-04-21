#ifndef PINCONFIG_H
#define PINCONFIG_H

#include <QObject>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QButtonGroup>

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

signals:
    
public slots:
    
};

#endif // PINCONFIG_H
