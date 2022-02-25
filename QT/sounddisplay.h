#ifndef SOUNDDISPLAY_H
#define SOUNDDISPLAY_H

#include <QWidget>
#include "timedomain.h"
#include "frequencydomaindisplay.h"
#include <iostream>
#include "external/ECE496-Backend/src/audiofile.h"

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

    AudioFile soundFile;

    /*
     * Widgets
     */
    // Play button that will startthe audio and start the cursor advancing
    QPushButton* playButton;

    // Stop button that will stop the audio and stops the cursor from advancing
    QPushButton* stopButton;

    // Time domain which displayed the entire sound wave
    TimeDomain* timeDomain;

    // Frequency domain which displays the fft of the audio at the selected cursor time
    FrequencyDomainDisplay* frequencyDisplay;


    /*
     * Layouts
     */

    // The layout of the entire widget
    QVBoxLayout* mainLayout;

    // The layout of the time/frequency domain section
    QHBoxLayout* domainLayout;

    // The layout of button control panel
    QHBoxLayout* buttonLayout;

    /*
     * Functions
     */
public slots:
    //Draws the file
    void drawWaveFromFile(QString file);

    // Stops the file stored in the selectedFile from playing
    void stopFile();

private slots:
    virtual void onPlayButtonClicked();
    //
};

#endif // SOUNDDISPLAY_H
