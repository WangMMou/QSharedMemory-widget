#include "widget.h"

#include <QApplication>
#include <QWindow>
#include "windows.h"

#include <QVBoxLayout>
#include <QLabel>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
