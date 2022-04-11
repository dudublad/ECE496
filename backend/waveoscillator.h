#ifndef WAVEOSCILLATOR_H
#define WAVEOSCILLATOR_H

#include <string>
#include <math.h>
#include <cmath>
#include <QtMath>

typedef enum {
    Wave_Sin,
    Wave_Square,
    Wave_SawTooth,
    Wave_Noise
} WaveType;

class WaveOscillator
{       
    private:
        double frequency;
        double amplitude;
        double phase;
        double duration;
        //int size;
        WaveType type;

        void generateSin(int size);
        void generateSquare(int size);
        void generateSawtooth(int size);
        void generateNoise(int size);

    public:
    //Constructors
        WaveOscillator();
        WaveOscillator(double amplitude_in, double frequency_in,
             double phase_in, double duration_in, WaveType type_in);
        ~WaveOscillator();
     //TEMP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     //TODO: make values private & accessible w a function
        double* values = NULL;
    //Set private values
        void setFrequency(double frequency);
        void setAmplitude(double amplitude);
        void setPhase(double phase);
        void setDuration(double duration);
        void setType(WaveType type);

    //Getters
        double getFrequency();
        double getAmplitude();
        double getPhase();
        double getDuration();
        WaveType getType();

    //Generate Wave Functions
        void generate();
};

#endif // WAVEOSCILLATOR_H
