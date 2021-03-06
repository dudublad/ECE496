#include "audiofilter.h"
#include "QDir"

audioFilter::audioFilter()
{
}

void audioFilter::generateFilter(QString filePath, QString originalPath, double &yscaling){
    try{
        this->input.openFile(originalPath.toStdString(), false, false);
        std::vector<double> coeff = this->coeffGen.generateFIRCoeff(
                this->freqCutoff1,
                this->freqCutoff2,
                this->filterType,
                this->windowType
            );
        this->fir.setCoefficients(coeff);
        std::vector<double> firBuffer;

        double max_value = 0;
        while (!input.isFinished()){
            double value = fir.tick(input.tick());
            max_value = std::max(max_value, value);
            firBuffer.push_back(value);
        }

        input.closeFile();
        this->output.openFile(filePath.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);
        for (long i = 0; i < firBuffer.size(); i++){
            output.tick(firBuffer[i]/max_value);
        }
        this->output.closeFile();
        yscaling = max_value;
    } catch (stk::StkError &error) {
        error.printMessage();
    }
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
