#include "spaghettowidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    spaghettoWidget w;
    /*w.addEntry(30,30);
    w.addEntry(30,-30);
    w.addEntry(-30,-30);
    w.addEntry(-30,30);
    w.addEntry(30,30);*/
    w.show();
    return a.exec();
}
