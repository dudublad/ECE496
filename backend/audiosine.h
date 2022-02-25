#ifndef AUDIOSINE_H
#define AUDIOSINE_H

#include "SineWave.h"
#include "FileWvOut.h"
#include "audiofile.h"
#include "QStringList"

class audioSine: public AudioFile
{
public:

    // assigns an id to object
    audioSine();

    // change sine frequency (aka pitch)
    void setFrequency(float freq);

    // change length of sine wave file generation
    void setDuration(float len);

    // set the file path of location of generated file
    void setFilePath(QString filePath);

    QString getFilePath();

    // generate the sine.wav file
    void generateSine();

private:
    stk::SineWave sineWave;
    QString filePath;
    stk::FileWvOut output;
    float durationSecs = 0.1F;

    static int id;
    const int currentId;
};

#endif // AUDIOSINE_H
