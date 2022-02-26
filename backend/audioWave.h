#ifndef AUDIOWAVE_H
#define AUDIOWAVE_H

#include "SineWave.h"
#include "FileWvOut.h"
#include "audiofile.h"
#include "QStringList"
#include "wave.h"

class audioWave: public AudioFile
{
public:

    // assigns an id to object
    audioWave();

    // change sine frequency (aka pitch)
    void setFrequency(float freq);

    // change length of sine wave file generation
    void setDuration(float len);

    // change the wave type
    void setWaveType(WaveType type);

    // set the file path of location of generated file
    void setFilePath(QString filePath);

    QString getFilePath();

    // generate the sine.wav file
    void generateSine();

private:
    wave gen_wave;
    QString filePath;
    stk::FileWvOut output;

    static int id;
    const int currentId;
};

#endif // AUDIOWAVE_H
