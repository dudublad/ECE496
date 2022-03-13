#ifndef OUTPUTSOUNDDISPLAY_H
#define OUTPUTSOUNDDISPLAY_H

#include "sounddisplay.h"

class OutputSoundDisplay : public SoundDisplay
{
    Q_OBJECT
private:
    //Points to the same input vector as the one in InputScrollView
    QVector<SoundDisplay*>* inputs = nullptr;

    //Output values
    QVector<double> outputBuf;

    void generateOutputFile();

    QString filepath;

public:
    OutputSoundDisplay(QVector<SoundDisplay*>* input_vec, QWidget *parent);


public slots:
    void generateOutput();
};

#endif // OUTPUTSOUNDDISPLAY_H
