#ifndef AUDIOCONFIG_H
#define AUDIOCONFIG_H

#include <RtAudio.h>
#include <Stk.h>

// parent class dealing with streams + volume. main sound config
class AudioConfig

{
public:
    // default contructor
    AudioConfig();

    // where sound is played
    RtAudio dac; // digital to analogue converter

    // obtains the necessary device outputs for RT audio
    RtAudio::StreamParameters* getStreamParams();
    RtAudioFormat getAudioFormat();

    // determines if current instance of RT audio stream is playing
    bool isPlaying();

    // closes the stream
    void closeStream();

    // begins/resumes the stream
    void startStream();

    // pauses the stream
    void pauseStream();

    // gets the current time of stream
    double getStreamTime();

    // set playback time for stream
    void setStreamTime(double time);

    ~AudioConfig();

private:
     //RtAudio API variables
    RtAudio::StreamParameters streamParameters;
    RtAudioFormat audioFormat;

};

#endif // AUDIOCONFIG_H
