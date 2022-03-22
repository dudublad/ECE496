#ifndef FREQUENCYDOMAINDISPLAY_H
#define FREQUENCYDOMAINDISPLAY_H

#include "qcustomplot.h"

class FrequencyDomainDisplay : public QCustomPlot
{
    Q_OBJECT

public:
    FrequencyDomainDisplay(QWidget *parent = Q_NULLPTR);
    ~FrequencyDomainDisplay();

    // Plots the samples stored in the samples attribute on its wavePlot attribute
    void plot();

    // Sets FFT coefficients for to display on the graph
    void setCoefficients(QVector<double> coeffs);
    void setSamples(QVector<double> samples);
private:
    QVector<double> coefficients;
    QCPGraph *fftPlot;

};

#endif // FREQUENCYDOMAINDISPLAY_H
