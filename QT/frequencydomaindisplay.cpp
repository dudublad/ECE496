#include "frequencydomaindisplay.h"
#include "Stk.h"

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

//The x-axis will be scaled to the largest possible value
//where coefs[i] is bigger than this value
#define COEFS_X_LIMIT 0.01

//X-axis will be 20% bigger to look neater
#define X_AXIS_EXTENSION 1.2

void FrequencyDomainDisplay::plot()
{
    int numCoeffs = coefficients.size();
    QVector<double> vec(numCoeffs);
    QVector<double> neg_vec(numCoeffs); //Negative plot
    double max_x = 0;
    for(int i = 1;i < numCoeffs;i++)
    {
       vec[i] = i * (stk::Stk::sampleRate()/(2*(numCoeffs-1)));
       neg_vec[i] = -1 * vec[i];

       if(coefficients[i] > COEFS_X_LIMIT) {
           max_x = vec[i];
       }
    }

    fftPlot->setData(vec, coefficients);
    fftPlot->addData(neg_vec, coefficients);

    yAxis->setRange(QCPRange(0, 1));

    if(vec.size() > 0)
    {

        xAxis->setRange(QCPRange(-X_AXIS_EXTENSION*max_x, X_AXIS_EXTENSION*max_x));
    }
    else
    {
        xAxis->setRange(QCPRange(-1,1));
    }
    //end
    replot();
    //std::cout << "Frequency Plot exited " << std::endl;
}
