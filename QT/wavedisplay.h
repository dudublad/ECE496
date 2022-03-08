#ifndef WAVEDISPLAY_H
#define WAVEDISPLAY_H

#include "sounddisplay.h"
#include "wavegenerator.h"

class WaveDisplay : public SoundDisplay
{
    Q_OBJECT
public:
    WaveDisplay(QWidget *parent);

    /*
     *  Data attributes
     */
    int waveFrequency;

    /*
    * Subwidgets custom to SineWave
    */
    WaveGenerator wave;

    // Says set Frequency over top the slider and other label
    QLabel* titleLabel;

    // Displays the current slider frequency setting
    QLabel* frequencyLabel;

    // The frequency Slider
    QSlider* frequencySlider;

    // Where the title and the control panel live
    QVBoxLayout* frequencyLayout;

    // Contains the buttons on the frequency Layout
    QHBoxLayout* frequencyControlLayout;

    QComboBox* waveTypeSelector;

private:
    void plotWave();
    void playSound();

public slots:
    void frequencySliderChange(int value);
    void frequencySliderStop();
    void onPlayButtonClicked();
    void waveTypeIndexChanged(int index);

};

#endif // WAVEDISPLAY_H
