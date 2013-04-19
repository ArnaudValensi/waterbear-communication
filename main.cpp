#include "GuiController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuiController w;
    w.show();
    
    return a.exec();
}
