#ifndef TIMEDOMAIN_H
#define TIMEDOMAIN_H

#include "qcustomplot.h"
#include <QAudioBuffer>
#include  <iostream>
class QAudioDecoder;

#define START_INPUT_ID 1
#define OUTPU_ID 0

// Class used to display the time domain plot of a signal, inherits the QCustomPlot functionality
class TimeDomain : public QCustomPlot
{
    Q_OBJECT

public:

    QString currentFile;
    QAudioDecoder *decoder;
    QAudioBuffer buffer;
    QVector<double> samples;
    QCPGraph *wavePlot;
    int sampleRate;
    double sampleScale = 1.0;

    double yScaling = 1.0;
    double yMax = 1.0;
    double yMin = -1.0;

    TimeDomain(QWidget *parent = Q_NULLPTR);
    ~TimeDomain();

    // Sets a new file source for the decoder which will automatically run setBuffer and plot when complete
    void setSource(const QString &fileName);

    QString getSourceFile();

public slots:
    // Sets the samples in the samples attribute with information from the decoder when decoding completes
    void setBuffer();

    // Plots the samples stored in the samples attribute on its wavePlot attribute
    void plot();

    // Adds samples from a vector of doubles and stores them in the samples attribute, does not automatically plot
    void appendSamples(QVector<double> incomingSamples,int sample_rate);

    //Returns the value stored in the sampleRate attribute
    int getSampleRate();

signals:
    void plotStarted();
    void plotFinished();

private:
    // Gets the peak value of the specific audio format
    qreal getPeakValue(const QAudioFormat& format);
};
#endif
