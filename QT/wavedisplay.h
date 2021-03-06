#ifndef WAVEDISPLAY_H
#define WAVEDISPLAY_H

#include "sounddisplay.h"
#include "wavegenerator.h"
#include <QDateTime>

#define GENERATE_LIMIT_MS 1000

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

    //1 for sine,2 for square, 3 for saw
    WaveType waveType;

    /*
     * Keeps track of when the last wave was generated
     * This is limited by GENERATE_LIMIT_S
     */
    qint64 last_generate_time_ms;

    /*
    * Subwidgets custom to SineWave
    */
    WaveGenerator wave;

    // Says set Frequency over top the slider and other label
    QLabel* frequencyLabel;

    // Displays the current slider frequency setting
    QSpinBox* frequencySpinBox;

    // The frequency Slider
    QSlider* frequencySlider;

    // Contains the buttons on the frequency Layout
    QHBoxLayout* frequencyControlLayout;

    QComboBox* waveTypeSelector;

    // The Button that generates the wave
    QPushButton* generateButton;

    //
    QDoubleSpinBox * amplitudeSpinBox;
    QLabel* amplitudeLabel;

    QSlider* amplitudeSlider;

private:
    void plotWave();

public slots:
    void frequencySliderChange(int value);
    void onSpinBoxChanged(int value);
    void waveTypeIndexChanged(int index);
    void generateButtonPushed();
    void amplitudeSliderChange(int value);
    void amplitudeSpinBoxChange(double value);
};

#endif // WAVEDISPLAY_H
