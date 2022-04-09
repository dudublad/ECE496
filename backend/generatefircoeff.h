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

typedef enum {
    rect,
    hann,
    hamm,
    bart,
    black
} WindowType;

class generateFirCoeff{
public:
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
    std::vector<double> generateFIRCoeff(double fc1, double fc2, FilterType filter_type, WindowType window_type);
    //Generates F domain plot of the FIR filter
    std::vector<double> generateFIRPlot(double fc1, double fc2, FilterType filter_type, WindowType window_type);
    void setM(int newM);

private:
    int M = 500; //TODO: this should be num_taps
    double fs = stk::Stk::sampleRate();

    //Specific generator functions
    std::vector<double> generate_fc(double ft1, double ft2, int M, FilterType filter_type);
    std::vector<double> generateLPF(double ft, int M);
    std::vector<double> generateHPF(double ft, int M);
    std::vector<double> generateBPF(double ft1, double ft2, int M);
    std::vector<double> generateBSF(double ft1, double ft2, int M);

    //Window functions
    std::vector<double> window_fc(std::vector<double> input, int M, WindowType window_type);
    std::vector<double> window_hann(std::vector<double> input, int M);
    std::vector<double> window_hamm(std::vector<double> input, int M);
    std::vector<double> window_bart(std::vector<double> input, int M);
    std::vector<double> window_black(std::vector<double> input, int M);

    //Used internally
    int MCheck(int M, FilterType filter_type);
    double my_sinc(int i, int M, double f);

    //Used for testing - get rid of eventually probably
    void printCoeffs(std::vector<double> input, FilterType filter_type);
};


#endif // GENERATEFIRCOEFF_H
