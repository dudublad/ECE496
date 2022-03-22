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
class SoundDisplay : public QWidget
{
    Q_OBJECT
public:
    // if this breaks insert QWidget *parent = Q_NULLPTR
    SoundDisplay(QWidget *parent);
    ~SoundDisplay();
    void changeFile(QString path);

    /*
     * Data members
     */

    // cursor which tracks at what point we are in the sound
    double cursor;

    // The selected file that will play on the widget
    QString selectedFile;

    // Volume of the played sound, Scale: 0-100
    int volume;

    // Id value for use in parent classes,id for output is always 0
    int inputId;

    AudioFile soundFile;

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

    // Label that displays current id
    QLabel* idLabel;

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

private slots:
    virtual void onPlayButtonClicked();
    //
};

#endif // SOUNDDISPLAY_H
