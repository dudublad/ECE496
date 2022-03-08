#include "wave.h"
#include <math.h>
#include <iostream>

//Constructors
wave::wave(){
    //TODO: How to set default values for a class
}
wave::wave(double amplitude_in, double frequency_in,
           double phase_in, double duration_in, std::string type_in){
    amplitude = amplitude_in;
    frequency = frequency_in;
    phase = phase_in;
    duration = duration_in;
    type = type_in;
    int size = ceil(duration * 44100);
    values = new double[size];

    generate();
}

wave::~wave(){
    if(values != NULL){
        delete[] values;
        values = NULL;
    }
}

//Setters
void wave::setAmplitude(double amplitude_in){
    //limit?
    amplitude = amplitude_in;
}
void wave::setFrequency(double freqeuncy_in){
    frequency = freqeuncy_in;
}
void wave::setPhase(double phase_in){
    phase = phase_in;
}
void wave::setDuration(double duration_in){
    //limit?
    duration = duration_in;
}
void wave::setType(std::string type_in){
    if(type_in == "sin" || type_in == "square"
            || type_in == "saw") type = type_in;
    if(type_in == "sawtooth") type = "saw";
}

//Generators
void wave::generate(){
    //Clear previous values
    if(values != NULL) delete[] values;

    //TODO: fix #define so this can use fSampling
    int size = ceil(duration * 44100);
    values = new double[size];

    //Generate based on wave type
    if(type == "sin"){
        generateSin(size);
    }
    else if (type == "square"){
        generateSquare(size);
    }
    else if (type == "saw"){
        generateSawtooth(size);
    }
    else{
        return;
    }
}

void wave::generateSin(int size){
    for(int i = 0; i < size; i++){
        //TODO: tSampling is not working here for some reason idk
        values[i] = amplitude*sin((2*M_PI*frequency*0.00002267573*i) + phase);
    }
}

void wave::generateSquare(int size){
    for(int i = 0; i < size; i++){
        //TODO: tSampling is not working here for some reason idk
        double temp = sin((2*M_PI*frequency*0.00002267573*i) + phase);
        temp > 0 ? values[i] = amplitude : values[i] = amplitude *-1;
    }
}

void wave::generateSawtooth(int size){
    double n = 44100/frequency;
    for(int i = 0; i < size; i++){
        values[i] = 2*((amplitude*(fmod(i + n*(phase/(2*M_PI)),n)))/n
                       - 0.5*amplitude);
    }
}
