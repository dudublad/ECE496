#include "mainwindow.h"
#include <iostream>
#include "fftw3.h"
#include "Stk.h"
#include "generatefircoeff.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    stk::Stk::setSampleRate(132300.0);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
