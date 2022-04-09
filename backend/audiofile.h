#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include "audioconfig.h"
#include "RtAudio.h"
#include "qstring.h"
#include "FileWvIn.h"

int tickFile( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
 double streamTime, RtAudioStreamStatus status, void *userData );

class AudioFile: public AudioConfig
{
public:

    // constructs object
    AudioFile();

    // opens file with given path
    void openFile(QString filePath);

    // changes current volume of opened file
    void changeVolume(float volume);

    stk::FileWvIn getInputFile();

    void closeFile();

    ~AudioFile();

private:

    // volume control
    float volume = 1;

    // the buffer
    unsigned int bufferFrames = stk::RT_BUFFER_SIZE * 3;

    // the file itself as an stk input
    stk::FileWvIn input;

    QString currentFile = "";
};

#endif // AUDIOFILE_H
