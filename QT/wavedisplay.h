#ifndef WAVEDISPLAY_H
#define WAVEDISPLAY_H

#include "sounddisplay.h"
#include "wavegenerator.h"

class WaveDisplay : public SoundDisplay
{
    Q_OBJECT
public:
    WaveDisplay(QWidget *parent, int id);

    /*
     *  Data attributes
     */
    int waveFrequency;

    double amplitude;

    /*
    * Subwidgets custom to SineWave
    */
    WaveGenerator wave;

    // Says set Frequency over top the slider and other label
    QLabel* titleLabel;

    // Displays the current slider frequency setting
    QSpinBox* frequencyLabel;

    // The frequency Slider
    QSlider* frequencySlider;

    // Where the title and the control panel live
    QVBoxLayout* frequencyLayout;

    // Contains the buttons on the frequency Layout
    QHBoxLayout* frequencyControlLayout;

    QComboBox* waveTypeSelector;

    // The Button that generates the wave
    QPushButton* generateButton;

    //
    QLabel* amplitudeLabel;

    QSlider* amplitudeSlider;

private:
    void plotWave();

public slots:
    void frequencySliderChange(int value);
    void frequencySliderStop();
    void onSpinBoxChanged(int value);
    void waveTypeIndexChanged(int index);
    void generateButtonPushed();
    void amplitudeSliderChange(int value);
    void amplitudeSliderStop();

signals:
    void waveGenerated(int waveFrequency);
};

#endif // WAVEDISPLAY_H
