#include "audiofile.h"

AudioFile::AudioFile()
{
}

stk::FileWvIn AudioFile::getInputFile()
{
    return input;
}

void AudioFile::openFile(QString filePath){

    try{
        this->input.openFile(filePath.toStdString());
        this->currentFile = filePath;
    } catch (stk::StkError &error) {
        error.printMessage();
    }

    this->input.setRate((double) (this->input.getFileRate() / stk::Stk::sampleRate()));

    try {
        this->dac.openStream(this->getStreamParams(), NULL, this->getAudioFormat(),
                             (unsigned int) stk::Stk::sampleRate(), &this->bufferFrames, &tickFile, (void*)&this->input);
    }  catch (RtAudioError &error) {
        error.printMessage();
    }
}

void AudioFile::changeVolume(float volume){
    std::cout << "changing volume to: " << volume << " for this file: " << this->currentFile.toStdString() << std::endl;
    this->input.normalize(volume);
}

void AudioFile::closeFile(){
    this->closeStream();
    this->input.closeFile();
}

AudioFile::~AudioFile(){
    this->closeStream();
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
