#include "mainwindow.h"
#include "TestClass.h"
#include "SineWave.h"
#include "Noise.h"
#include <iostream>

#include <QApplication>
//using namespace stk;

//Link Ws2_32.lib for STK
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
    stk::StkFloat output;
    stk::Noise noise;

    for ( unsigned int i=0; i<20; i++ ) {
        output = noise.tick();
        std::cout << "i = " << i << " : output = " << output << std::endl;
      }

    //Testing the backend. TODO: Remove
    TestClass::testHelloWorld();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
