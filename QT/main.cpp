#include "mainwindow.h"
#include "TestClass.h"
#include "SineWave.h"
#include "Noise.h"
#include <iostream>

#include <QApplication>

//Link Ws2_32.lib for STK
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
    //Testing the backend. TODO: Remove
    TestClass::testHelloWorld();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
