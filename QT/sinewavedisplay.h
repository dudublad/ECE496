#ifndef SINEWAVEDISPLAY_H
#define SINEWAVEDISPLAY_H

#include "sounddisplay.h"

class SineWaveDisplay : public SoundDisplay
{
    Q_OBJECT
public:
    SineWaveDisplay(QWidget *parent);

    /*
     *  Data attributes
     */
    int waveFrequency;

    /*
    * Subwidgets custom to SineWave
    */

    // Says set Frequency over top the slider and other label
    QLabel* titleLabel;

    // Displays the current slider frequency setting
    QLabel* frequencyLabel;

    // The frequency Slider
    QSlider* frequencySlider;

    /*
     * Non signaled functions
     */
    void setFrequency();

    QGridLayout* frequencyLayout;

public slots:
    void frequencySliderStop(int value);

};

#endif // SINEWAVEDISPLAY_H
