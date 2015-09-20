#include "mainwindow.h"
#include "function.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qInstallMessageHandler(logMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
