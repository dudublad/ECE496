#include "audiofile.h"

AudioFile::AudioFile()
{
}

void AudioFile::openFile(QString filePath){
    try{
        this->input.openFile(filePath.toStdString());
    } catch (stk::StkError &error) {
        error.printMessage();
    }

    this->input.setRate((double) (this->input.getFileRate() / stk::Stk::sampleRate()));

    //TODO: FIX SAMPLING RATE FOR SOUND
    try {
        this->dac.openStream(this->getStreamParams(), NULL, this->getAudioFormat(),
                             (unsigned int) stk::Stk::sampleRate(), &this->bufferFrames, &tickFile, (void*)&this->input);
    }  catch (RtAudioError &error) {
        error.printMessage();
    }
}

void AudioFile::changeVolume(float volume){
    this->input.normalize(volume);
}

AudioFile::~AudioFile(){
    this->input.closeFile();
}

int tickFile( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    stk::FileWvIn *input = (stk::FileWvIn *) userData;
    auto *samples = (stk::StkFloat *) outputBuffer;
    for ( unsigned int i=0; i<nBufferFrames; i++ ){
        try {
            *samples++ = input->tick();
        }  catch (stk::StkError &error) {
            error.printMessage();
        }
    }
    return 0;
}
