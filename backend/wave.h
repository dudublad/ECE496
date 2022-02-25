#ifndef fSampling
    #define fSampling = 44100;
#endif

#ifndef tSampling
    #define tSampling = 0.00002267573;
#endif

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifndef WAVE_H
#define WAVE_H

#include <string>
#include <math.h>
#include <cmath>

class wave
{       
    private:
        double frequency;
        double amplitude;
        double phase;
        double duration;
        //int size;
        std::string type;

    public:
    //Constructors
        wave();
        wave(double amplitude_in, double frequency_in,
             double phase_in, double duration_in, std::string type_in);
        ~wave();
     //TEMP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     //TODO: make values private & accessible w a function
        double* values;
    //Set private values
        void setFrequency(double frequency);
        void setAmplitude(double amplitude);
        void setPhase(double phase);
        void setDuration(double duration);
        void setType(std::string type);
    //Generate Wave Functions
        void generate();
        void generateSin(int size);
        void generateSquare(int size);
        void generateSawtooth(int size);
};

#endif // WAVE_H
