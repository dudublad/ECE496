#include "mainwindow.h"
#include "TestClass.h"
#include <iostream>
#include "fftw3.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Testing the backend. TODO: Remove
    TestClass::testHelloWorld();

    QVector<double>test = QVector<double>(44100);
    double f=1;
    for(int n = 0; n < 44100; n++){
        test[n] = sin(2*M_PI*f*0.00002267573);
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
