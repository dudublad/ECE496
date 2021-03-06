#ifndef AUDIOFILTER_H
#define AUDIOFILTER_H

#include "generatefircoeff.h"
#include "Stk.h"
#include "FileWvOut.h"
#include "FileWvIn.h"
#include "Fir.h"

class audioFilter
{
public:
    audioFilter();
    void generateFilter(QString filePath, QString originalPath, double &yscaling);
    void setFreqCutoff1(double cutoff);
    void setFreqCutoff2(double cutoff);
    void setFilterType(int type);
    void setWindowType(int type);

    // vars required for generation
    double freqCutoff1;
    double freqCutoff2;
    FilterType filterType;
    WindowType windowType;

private:

    // coefficient generator
    generateFirCoeff coeffGen;

    // finite impulse response (stk filtering)
    stk::Fir fir;

    // the file to apply filter on
    stk::FileWvIn input;

    // the file to write to, should be the same as input
    stk::FileWvOut output;


};

#endif // AUDIOFILTER_H
