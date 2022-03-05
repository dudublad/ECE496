#include "audioconfig.h"

AudioConfig::AudioConfig()
{
    this->streamParameters.deviceId = this->dac.getDefaultInputDevice();
    this->streamParameters.nChannels = 1;
    this->audioFormat = (sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
}

RtAudio::StreamParameters* AudioConfig::getStreamParams(){
    return &this->streamParameters;
}

RtAudioFormat AudioConfig::getAudioFormat(){
    return this->audioFormat;
}

bool AudioConfig::isPlaying(){
    return this->dac.isStreamRunning();
}

bool AudioConfig::isOpen(){
    return this->dac.isStreamOpen();
}

void AudioConfig::closeStream(){
    if (this->isOpen()){
        this->dac.closeStream();
    }
}

void AudioConfig::startStream(){
    try {
        if (this->isOpen() && !this->isPlaying()){
            this->dac.startStream();
        }
    }  catch (RtAudioError e) {
        e.printMessage();
    }

}

void AudioConfig::pauseStream(){
    std::cout << this->isPlaying() << std::endl;
    if (this->isOpen() && this->isPlaying()){
        std::cout << "should be pausing" << std::endl;
        this->dac.stopStream();
    }
}

void AudioConfig::setStreamTime(double time){
    this->dac.setStreamTime(time);
    if (this->isPlaying()){
        this->dac.startStream();
    }
    this->dac.stopStream();
}

AudioConfig::~AudioConfig(){
    this->dac.closeStream();
}
