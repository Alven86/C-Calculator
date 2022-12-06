#include "alvenmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlvenMainWindow w;
    w.show();

    return a.exec();
}
