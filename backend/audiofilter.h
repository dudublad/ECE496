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
    void generateFilter(QString filePath);
    void setFreqCutoff1(double cutoff);
    void setFreqCutoff2(double cutoff);
    void setFilterType(int type);
    void setWindowType(int type);

private:

    // coefficient generator
    generateFirCoeff coeffGen;

    // finite impulse response (stk filtering)
    stk::Fir fir;

    // the file to apply filter on
    stk::FileWvIn input;

    // the file to write to, should be the same as input
    stk::FileWvOut output;

    // vars required for generation
    double freqCutoff1;
    double freqCutoff2;
    FilterType filterType;
    WindowType windowType;

};

#endif // AUDIOFILTER_H
