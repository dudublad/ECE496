#include "generatefircoeff.h"
#include <Stk.h>

//Coef generation function - call this one
//inputs:
//for lpf/hpf, fc1 = cutoff frequency, fc2 = 0
//for bpf/bsp, fc1 = lower cutoff, fc2 = upper cutoff
//filter_type should be one of: "LPF", "HPF", "BPF, "BSF"
//window_type should be one of: "rect", "hann", "hamm", "bart", "black"
//window default should be "rect"
//returns empty vector for error
QVector<double> generateFIRCoeff(double fc1, double fc2, FilterType filter_type, WindowType window_type){
    double fs = stk::Stk::sampleRate();
    int M = 20; //TODO: this should be num_taps

    //Checks fc1, fc2 not greater than sampling frequency fs
    if(fc1 > fs) fc1 = fs;
    if(fc2 > fs) fc2 = fs;

    //Check M even for HPF, BPF, BSF
    M = MCheck(M, filter_type);

    //Calls filter gen based on type, with normalized ft value
    QVector<double> filter = generate_fc(fc1/fs, fc2/fs, M, filter_type);
    printCoeffs(filter, filter_type);

    //Returns windowed filter (defualt is rectuangular - unchanged)
    return window_fc(filter, M, window_type);

    //default returns empty QVector
    //return QVector<double>();
}

//reference: http://www.labbookpages.co.uk/audio/firWindowing.html
//-----------------------------------------------------------------------

//---------GENERATOR FUNCTIONS---------------------

//Decides which generator to call
QVector<double> generate_fc(double ft1, double ft2, int M, FilterType filter_type){
    switch(filter_type){
    case LPF:
        return generateLPF(ft1, M);
        break;
    case HPF:
        return generateHPF(ft1, M);
        break;
    case BPF:
        return generateBPF(ft1, ft2, M);
        break;
    case BSF:
        return generateBSF(ft1, ft2, M);
        break;
    default:
        return QVector<double>(); //default  returns empty vector
    }
}

QVector<double> generateLPF(double ft, int M){
    QVector<double> coeffs(M+1);

    //Sampling sinc function, with substitiution of M/2 (div by 0 case)
    for(int i = 0; i < M+1; i++){
        coeffs[i] = (i == M/2) ? 2*ft : my_sinc(i, M, ft);
    }

    return coeffs;
}

QVector<double> generateHPF(double ft, int M){
    QVector<double> coeffs(M+1);

    //Sampling sinc function, with substitiution of M/2 (div by 0 case)
    for(int i = 0; i < M+1; i++){
        coeffs[i] = (i == M/2) ? 1-2*ft : -1*my_sinc(i, M, ft);
    }

    return coeffs;
}

QVector<double> generateBPF(double ft1, double ft2, int M){
    if(ft1 == ft2) return QVector<double>();
    QVector<double> coeffs(M+1);

    //Sampling sinc function, with substitiution of M/2 (div by 0 case)
    for(int i = 0; i < M+1; i++){
        coeffs[i] = (i == M/2) ? 2*(ft2 - ft1) : my_sinc(i, M, ft2)-my_sinc(i, M, ft1);
    }

    return coeffs;
}

QVector<double> generateBSF(double ft1, double ft2, int M){
    if(ft1 == ft2) return QVector<double>();
    QVector<double> coeffs(M+1);

    //Sampling sinc function, with substitiution of M/2 (div by 0 case)
    for(int i = 0; i < M+1; i++){
        coeffs[i] = (i == M/2) ? 1 - 2*(ft2 - ft1) : my_sinc(i, M, ft1)-my_sinc(i, M, ft2);
    }

    return coeffs;
}

//-----------WINDOW FUNCTIONS------------------------

QVector<double> window_fc(QVector<double> input, int M, WindowType window_type){
    if(input.size() == 0) return input;

    switch(window_type){
    case rect:
        return input;
        break;
    case hann:
        return window_hann(input, M);
        break;
    case hamm:
        return window_hamm(input, M);
        break;
    case bart:
        return window_bart(input, M);
        break;
    case black:
        return window_black(input, M);
        break;
    }

    return input; //"rect" or unknown input returns unwindowed filter
}

QVector<double> window_hann(QVector<double> input, int M){
    for(int i = 0; i < input.size(); i++){
        input[i] = input[i] * (0.5 - 0.5*cos(2*M_PI*i/M));
    }
    return input;
}

QVector<double> window_hamm(QVector<double> input, int M){
    for(int i = 0; i < input.size(); i++){
        input[i] = input[i] * (0.54 - 0.46*cos(2*M_PI*i/M));
    }
    return input;
}

QVector<double> window_bart(QVector<double> input, int M){
    for(int i = 0; i < input.size(); i++){
        input[i] = input[i] * (1 - 2*abs(i - M/2)/M);
    }
    return input;
}

QVector<double> window_black(QVector<double> input, int M){
    for(int i = 0; i < input.size(); i++){
        input[i] = input[i] * (0.42 - 0.5*cos(2*M_PI*i/M) + 0.08*cos(4*M_PI*i/M));
    }
    return input;
}

//---------------------------------------------------

//HPF, BPF and BSFs must have odd size (even M)
//This is because of the implicit use of an all-pass filter
int MCheck(int M, FilterType filter_type){
    if(M%2 && filter_type != LPF){
        M+=1; //keep this print statement, as this addressess a user-input error
        std::cout << "For a " << filter_type << ", order must be an even number!\nThe order has been changed to " << M << "\n";
    }
    return M;
}

double my_sinc(int i, int M, double f){
    return sin(2*M_PI*f*(i - M/2))/(M_PI*(i - M/2));
}

void printCoeffs(QVector<double> input, FilterType filter_type){
    std::cout << filter_type <<" coeffs:";
    //Sampling sinc function, with substitiution of M/2 (div by 0 case)
    for(int i = 0; i < input.size(); i++){
        std::cout << " " << input[i] << " ";
    }
    std::cout << "\n";
}
