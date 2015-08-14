#include "mainwindow.h"
#include "logging_define.cpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    qInstallMessageHandler(logMessageOutput);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
