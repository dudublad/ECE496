#include "waveoscillator.h"
#include <math.h>
#include <iostream>
#include <Stk.h>

//Constructors
WaveOscillator::WaveOscillator(){
    //TODO: How to set default values for a class
    frequency = 20;
    amplitude = 1;
    duration = 2;
    phase = 0;
    type = Wave_Sin;
    values = NULL;
}
WaveOscillator::WaveOscillator(double amplitude_in, double frequency_in,
           double phase_in, double duration_in, WaveType type_in){
    amplitude = amplitude_in;
    frequency = frequency_in;
    phase = phase_in;
    duration = duration_in;
    type = type_in;
    int size = ceil(duration * stk::Stk::sampleRate());
    values = new double[size];

    generate();
}

WaveOscillator::~WaveOscillator(){
    if(values != NULL){
        delete[] values;
        values = NULL;
    }
}

//Setters
void WaveOscillator::setAmplitude(double amplitude_in){
    //limit?
    amplitude = amplitude_in;
}
void WaveOscillator::setFrequency(double freqeuncy_in){
    frequency = freqeuncy_in;
}
void WaveOscillator::setPhase(double phase_in){
    phase = phase_in;
}
void WaveOscillator::setDuration(double duration_in){
    //limit?
    duration = duration_in;
}
void WaveOscillator::setType(WaveType type_in){
    if(type_in == Wave_Sin || type_in == Wave_Square
            || type_in == Wave_SawTooth)
        type = type_in;
}

//Getters
double WaveOscillator::getFrequency()
{
    return frequency;
}
double WaveOscillator::getAmplitude()
{
    return amplitude;
}
double WaveOscillator::getPhase()
{
    return phase;
}
double WaveOscillator::getDuration()
{
    return duration;
}
WaveType WaveOscillator::getType()
{
    return type;
}

//Generators
void WaveOscillator::generate(){

    //Clear previous values
    if(values != NULL) delete[] values;

    //TODO: fix #define so this can use fSampling
    int size = ceil(duration * stk::Stk::sampleRate());
    values = new double[size];

    //Generate based on wave type
    if(type == Wave_Sin){
        generateSin(size);
    }
    else if (type == Wave_Square){
        generateSquare(size);
    }
    else if (type == Wave_SawTooth){
        generateSawtooth(size);
    }
    else{
        return;
    }
}

void WaveOscillator::generateSin(int size){
    for(int i = 0; i < size; i++){
        //TODO: tSampling is not working here for some reason idk
        values[i] = amplitude*sin((2*M_PI*frequency* (1.0 / stk::Stk::sampleRate()) *i) + phase);
    }
}

void WaveOscillator::generateSquare(int size){
    for(int i = 0; i < size; i++){
        //TODO: tSampling is not working here for some reason idk
        double temp = sin((2*M_PI*frequency* (1.0 / stk::Stk::sampleRate()) *i) + phase);
        temp > 0 ? values[i] = amplitude : values[i] = amplitude *-1;
    }
}

void WaveOscillator::generateSawtooth(int size){
    double n = stk::Stk::sampleRate()/frequency;
    for(int i = 0; i < size; i++){
        values[i] = 2*((amplitude*(fmod(i + n*(phase/(2*M_PI)),n)))/n
                       - 0.5*amplitude);
    }
}
