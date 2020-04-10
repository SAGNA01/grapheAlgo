#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication qAppli(argc, argv);
    MainWindow mainWin;
    mainWin.show();

    return qAppli.exec();
}
