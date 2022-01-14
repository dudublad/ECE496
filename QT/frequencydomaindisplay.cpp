#include "frequencydomaindisplay.h"

FrequencyDomainDisplay::FrequencyDomainDisplay(QWidget *parent)
    : QCustomPlot(parent)
{
    //constructor
    //connect(decoder, SIGNAL(fftReady()), this, SLOT(setBuffer()));
    fftPlot = addGraph();
    this->setInteraction(QCP::iRangeDrag,true);
    this->setInteraction(QCP::iRangeZoom,true);
    this->axisRects().at(0)->setRangeDrag(Qt::Horizontal);
    this->axisRects().at(0)->setRangeZoom(Qt::Horizontal);
}

FrequencyDomainDisplay::~FrequencyDomainDisplay()
{
    fftPlot->data()->clear();
    this->removePlottable(fftPlot);
}
void FrequencyDomainDisplay::setCoefficients(QVector<double> coeffs)
{
    this->coefficients = coeffs;
    plot();
}

void FrequencyDomainDisplay::plot()
{

    QVector<double> vec(coefficients.size());
    fftPlot->addData(vec, coefficients);

    yAxis->setRange(QCPRange(0, 1));

    if(vec.size() > 0)
    {

        xAxis->setRange(QCPRange(-1*vec.last(), vec.last()));
    }
    else
    {
        xAxis->setRange(QCPRange(0,vec.size()));
    }
    //end
    replot();
    //std::cout << "Frequency Plot exited " << std::endl;
}
