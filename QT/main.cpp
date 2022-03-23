#include "mainwindow.h"
#include <iostream>
#include "fftw3.h"
#include "Stk.h"
#include "generatefircoeff.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    stk::Stk::setSampleRate(132300.0);

    QVector<double>test = QVector<double>(44100);
    double f=1;
    for(int n = 0; n < 44100; n++){
        test[n] = sin(2*M_PI*f*0.00002267573*n);
    }

    QVector<double> lpfTest = generateFIRCoeff(0.23*132300.0, 0, "LPF", "rect");
    QVector<double> hpfTest = generateFIRCoeff(0.23*132300.0, 0, "HPF", "rect");
    QVector<double> bpfTest = generateFIRCoeff(0.23*132300.0, 0.4*132300.0, "BPF", "rect");
    QVector<double> bsfTest = generateFIRCoeff(0.23*132300.0, 0.4*132300.0, "BSF", "rect");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
