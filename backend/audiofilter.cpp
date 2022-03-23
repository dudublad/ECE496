#include "audiofilter.h"

audioFilter::audioFilter()
{
}

void audioFilter::openFile(QString filePath){
    try{
        this->input.openFile(filePath.toStdString());
        this->output.openFile(filePath.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);
    } catch (stk::StkError &error) {
        error.printMessage();
    }
}

void audioFilter::generateFile(){
    std::vector<double> coeff = this->coeffGen.generateFIRCoeff(
                this->freqCutoff1,
                this->freqCutoff2,
                this->filterType,
                this->windowType
            );
    this->clearCoeffs();
    this->fir.setCoefficients(coeff);

    while (!input.isFinished()){
        output.tick(fir.tick(input.tick()));
    }
}

void audioFilter::clearCoeffs(){
    std::vector<stk::StkFloat> empty;
    this->fir.setCoefficients(empty, true);
}

void audioFilter::setFreqCutoff1(double cutoff){
    this->freqCutoff1 = cutoff;
}

void audioFilter::setFreqCutoff2(double cutoff){
    this->freqCutoff2 = cutoff;
}

void audioFilter::setFilterType(int type){
    this->filterType = FilterType(type);
}

void audioFilter::setWindowType(int type){
    this->windowType = WindowType(type);
}
