#ifndef PINCONFIG_H
#define PINCONFIG_H

#include <QObject>
#include <QGroupBox>
#include <QLineEdit>

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
    
signals:
    
public slots:
    
};

#endif // PINCONFIG_H
