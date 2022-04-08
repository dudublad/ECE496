#ifndef WAVEGENERATOR_H
#define WAVEGENERATOR_H

#include "SineWave.h"
#include "FileWvOut.h"
#include "audiofile.h"
#include "QStringList"
#include "waveoscillator.h"

class WaveGenerator
{
public:

    // assigns an id to object
    WaveGenerator();

    // change sine frequency (aka pitch)
    void setFrequency(float freq);

    // change the amplitude of wave
    void setAmplitude(float amplitude);

    // change length of sine wave file generation
    void setDuration(float len);

    // change the wave type
    void setWaveType(WaveType type);

    // set the file path of location of generated file
    void setFilePath(QString filePath);

    // obtain the generated wave filepath
    QString getFilePath();

    // generate the sine.wav file
    void generateSine();

    WaveOscillator gen_wave;

private:
    QString filePath;
    stk::FileWvOut output;

    static int id;
    const int currentId;
};

#endif // WAVEGENERATOR_H
