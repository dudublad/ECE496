#include "generatefircoeff.h"
#include <Stk.h>

QVector<double> generateFIRCoeff(double fc1, double fc2, std::string filter_type){


    //Checks fc1, fc2 not greater than sampling frequency fs
    if(fc1 > fs) fc1 = fs;
    if(fc2 > fs) fc2 = fs;
    if(fc1 == fc2) return QVector<double>();

    if(filter_type == "LPF") return generateLPF(fc1, fs);

    //default returns empty QVector
    return QVector<double>();
}

QVector<double> generateLPF(double fc, double fs){
    int M = 20; //TODO: this should be num_taps
    QVector<double> coeffs(M+1);


    return coeffs;
}
