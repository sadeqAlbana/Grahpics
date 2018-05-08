#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle("fusion");
    //QApplication::setFont(QFont("Serif"));
    QApplication a(argc, argv);


    MainWindow w;
    w.show();

    return a.exec();
}
