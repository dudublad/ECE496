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
    return this->dac.isStreamOpen();
}

void AudioConfig::closeStream(){
    if (this->isPlaying()){
        this->dac.closeStream();
    }
}

void AudioConfig::startStream(){
    try {
        this->dac.startStream();
    }  catch (RtAudioError e) {
        e.printMessage();
    }

}

void AudioConfig::pauseStream(){
    if (this->isPlaying()){
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
