#ifndef TIMEDOMAIN_H
#define TIMEDOMAIN_H

#include "qcustomplot.h"
#include <QAudioBuffer>
#include  <iostream>
class QAudioDecoder;

class TimeDomain : public QCustomPlot
{
    Q_OBJECT

public:
    TimeDomain(QWidget *parent = Q_NULLPTR);
    ~TimeDomain();
    void setSource(const QString &fileName);

public slots:
    void setBuffer();
    void plot();
    void appendSamples(QVector<double> incomingSamples);

private:
    qreal getPeakValue(const QAudioFormat& format);
    QString currentFile;
    QAudioDecoder *decoder;
    QAudioBuffer buffer;
    QVector<double> samples;
    QCPGraph *wavePlot;
};
#endif
