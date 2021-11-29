#include "timedomain.h"
#include <QAudioDecoder>

TimeDomain::TimeDomain(QWidget *parent)
    : QCustomPlot(parent)
    , decoder(new QAudioDecoder(this))
{
    currentFile="";
    wavePlot = addGraph();
    setMinimumHeight(100);
    connect(decoder, SIGNAL(bufferReady()), this, SLOT(setBuffer()));
    connect(decoder, SIGNAL(finished()), this, SLOT(plot()));

}

TimeDomain::~TimeDomain()
{
    samples.clear();
    delete decoder;
    wavePlot->data()->clear();
    this->removePlottable(wavePlot);
}

void TimeDomain::setSource(const QString &fileName)
{
    if(currentFile != fileName)
    {
        currentFile = fileName;
        wavePlot->data()->clear();
        samples.clear();
        decoder->setSource(currentFile);
        decoder->start();
    }
}

void TimeDomain::setBuffer()
{
    std::cout << "Setting Buffer" << std::endl;
    buffer = decoder->read();
    qreal peak = getPeakValue(buffer.format());

    //CHECK in case of error constData may come in different Types
    const qint16 *data = buffer.constData<qint16>();
    int count = buffer.sampleCount() / 2;
    for (int i=0; i<count; i++){
        double val = data[i]/peak;
        samples.append(val);
    }
    std::cout << "Setting Buffer Exited" << std::endl;
}

void TimeDomain::appendSamples(QVector<double> incomingSamples)
{
    samples.clear();
    for( int i = 0; i< incomingSamples.length(); i++)
    {
        samples.append(incomingSamples[i]);
    }
}

void TimeDomain::plot()
{
    std::cout << "Plotting" << std::endl;
    QVector<double> vec(samples.size());
    std::cout << "Samples size is " << samples.size() << std::endl;
    for (int i=0; i<vec.size(); i++)
        vec[i] = i;
    wavePlot->addData(vec, samples);
    yAxis->setRange(QCPRange(-1, 1));
    xAxis->setRange(QCPRange(0, samples.size()));
    replot();
    std::cout << "Plot exited" << std::endl;
}

qreal TimeDomain::getPeakValue(const QAudioFormat &format)
{
    qreal peak(0);
    if(format.isValid())
    {
        if(format.sampleFormat() == QAudioFormat::Unknown)
        {
            //no-op
        }
        if(format.sampleFormat() == QAudioFormat::Float)
        {
            peak = 1.0003;
        }
        if(format.sampleFormat() == QAudioFormat::UInt8)
        {
            peak = UINT_MAX;
        }
        if(format.sampleFormat() == QAudioFormat::Int16)
        {
            peak = SHRT_MAX;
        }
        if(format.sampleFormat() == QAudioFormat::Int32)
        {
            peak = INT_MAX;
        }
    }
    return peak;
}
