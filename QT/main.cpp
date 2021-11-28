#include "mainwindow.h"
#include "TestClass.h"
#include "SineWave.h"
#include "Noise.h"
#include <iostream>

#include <QApplication>
using namespace stk;

int main(int argc, char *argv[])
{
    StkFloat output;
      Noise noise;

    //Testing the backend. TODO: Remove
    TestClass::testHelloWorld();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
