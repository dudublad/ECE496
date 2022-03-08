#ifndef SINEWAVEDISPLAY_H
#define SINEWAVEDISPLAY_H

#include "sounddisplay.h"
#include "audiosine.h"

class SineWaveDisplay : public SoundDisplay
{
    Q_OBJECT
public:
    SineWaveDisplay(QWidget *parent, int id);

    /*
     *  Data attributes
     */
    int waveFrequency;

    /*
    * Subwidgets custom to SineWave
    */
    audioSine sinWave;

    // Says set Frequency over top the slider and other label
    QLabel* titleLabel;

    // Displays the current slider frequency setting
    QDoubleSpinBox* frequencyLabel;

    // The frequency Slider
    QSlider* frequencySlider;

    /*
     * Non signaled functions
     */
    void setFrequency(int freq);

    // Where the title and the control panel live
    QVBoxLayout* frequencyLayout;

    // Contains the buttons on the frequency Layout
    QHBoxLayout* frequencyControlLayout;

private:
    void plotWave();
    void playSound();

public slots:
    void frequencySliderChange(int value);
    void frequencySliderStop();
    void onPlayButtonClicked();
    void onSpinBoxChanged(double value);

};

#endif // SINEWAVEDISPLAY_H
