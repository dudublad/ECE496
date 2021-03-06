#ifndef SOUNDDISPLAY_H
#define SOUNDDISPLAY_H

#include <QWidget>
#include "timedomain.h"
#include "frequencydomaindisplay.h"
#include <iostream>
#include "backend/audiofile.h"
#include "effectpanel.h"
#include <string>
#include <QAudioDecoder>
#include "fft.h"
#include <QCheckBox>

class SoundDisplay : public QWidget
{
    Q_OBJECT
public:
    // if this breaks insert QWidget *parent = Q_NULLPTR
    SoundDisplay(QWidget *parent);
    ~SoundDisplay();
    void changeFile(QString path);
    static const int RECORDED_SOUND_TYPE = 1;
    static const int WAVE_SOUND_TYPE = 2;
    static const int OUTPUT_SOUND_TYPE = 3;
    void openFile();

    // copys the original file to the effect file
    void copyFileToEffectFile();

    // sets the effect file name to /this/file/path/name_effects.wav
    void setEffectFile(QString path);

    /*
     * Data members
     */

    // cursor which tracks at what point we are in the sound
    double cursor;

    // name of the ORIGINAL file
    QString fileName;

    // The selected file that will play on the widget
    // it is now the _effect appended file always
    QString selectedFile;

    // Volume of the played sound, Scale: 0-100
    int volume;

    //1 for recordedSound, 2 for wave, 3 for output
    int soundType;
    //Plot Properties
    //How much to scale the plotted graph
    double yScaling = 1;
    double yMax = 1.0;
    double yMin = -1.0;

    // Id value for use in parent classes,id for output is always 0
    int inputId;

    //Should this wave be added to the superimposed output
    bool addToOutput;

    AudioFile soundFile;

    audioFilter audioFilterData;
    /*
     * Widgets
     */
    // Play button that will startthe audio and start the cursor advancing
    QPushButton* playButton;

    // Stop button that will stop the audio and stops the cursor from advancing
    QPushButton* stopButton;

    // Button that toggles the effect panel
    QPushButton* toggleEffectPanelButton;

    // Button that deletes the input
    QPushButton* removeInputButton;

    // Time domain which displayed the entire sound wave
    TimeDomain* timeDomain;

    // Frequency domain which displays the fft of the audio at the selected cursor time
    FrequencyDomainDisplay* frequencyDisplay;

    // Where the buttons for the effects are located
    EffectPanel* effectPanel;

    // Placeholder Widget that holds the buttons so layouts can be used
    QWidget *buttonHolder;

    // Controls the volume for that one
    QSlider* volumeSlider;

    // Label for Volume
    QLabel *volumeLabel;

    /*
     * Layouts
     */

    // The layout of the entire widget
    QHBoxLayout* mainLayout;

    // The layout of the time/frequency domain section
    QHBoxLayout* domainLayout;

    // The layout of button control panel
    QGridLayout* buttonLayout;

    // Checkbox to add wave to output
    QCheckBox* addToOutputCheckBox;

    // Effect Panel Layout
    //QGridLayout* effectLayout;


    /*
     * Functions
     */

public slots:
    //Draws the file
    void drawWaveFromFile(QString file);

    // Stops the file stored in the selectedFile from playing
    void stopFile();

    //Toggles the visibility of the Effect Panel on the right
    void toggleEffectPanel();

    // Triggered when remove input button is pushed
    void removeInputButtonPushed();

    void volumeChanged(int volume);

    void addToOutputStateChanged(int state);

signals:
    void inputRemoved(SoundDisplay* toRemove);
    void filterAdded(SoundDisplay* sourceDisplay);
    void playButtonPressed(SoundDisplay* sourceDisplay);
    void waveGenerated(SoundDisplay* sourceDisplay);
    void superpositionStateChanged();

private slots:
    void onPlayButtonClicked();
    void generateEffect(audioFilter filter);
};

#endif // SOUNDDISPLAY_H
