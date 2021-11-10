#include "mainwindow.h"
#include "TestClass.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Testing the backend. TODO: Remove
    TestClass::testHelloWorld();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
