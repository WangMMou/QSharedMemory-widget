#include "aw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    aW w;
    //w.move(5000,5000);
    w.show();
    return a.exec();
}
