#ifndef GENERATEFIRCOEFF_H
#define GENERATEFIRCOEFF_H

#include <QBuffer>
#include <Stk.h>

typedef enum {
    LPF,
    HPF,
    BPF,
    BSF
} FilterType;

//Coef generation function - call this one
//output:
//vector of floats - FIR filter coefficients (see stk::FIR)
//inputs:
//for lpf/hpf, fc1 = cutoff frequency, fc2 = 0
//for bpf/bsp, fc1 = lower cutoff, fc2 = upper cutoff
//filter_type should be one of: "LPF", "HPF", "BPF, "BSF"
//window_type should be one of: "rect", "hann", "hamm", "bart", "black"
//window default should be "rect"
//returns empty vector for error
QVector<double> generateFIRCoeff(double fc1, double fc2, std::string filter_type, std::string window_type);


//IGNORE THESE --------------------------------------------
//Specific generator functions
//Do not call these!
QVector<double> generate_fc(double ft1, double ft2, int M, std::string filter_type);
QVector<double> generateLPF(double ft, int M);
QVector<double> generateHPF(double ft, int M);
QVector<double> generateBPF(double ft1, double ft2, int M);
QVector<double> generateBSF(double ft1, double ft2, int M);

//Window functions
QVector<double> window_fc(QVector<double> input, int M, std::string window_type);
QVector<double> window_hann(QVector<double> input, int M);
QVector<double> window_hamm(QVector<double> input, int M);
QVector<double> window_bart(QVector<double> input, int M);
QVector<double> window_black(QVector<double> input, int M);

//Used internally
int MCheck(int M, std::string filter_type);
double my_sinc(int i, int M, double f);

//Used for testing - get rid of eventually probably
void printCoeffs(QVector<double> input, std::string filter_type);

#endif // GENERATEFIRCOEFF_H
