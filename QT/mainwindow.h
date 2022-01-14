#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtMultimedia/QAudioInput>
#include <QBuffer>
#include "qcustomplot.h"
#include <QMainWindow>
#include "timedomain.h"
#include <SineWave.h>
#include <RtAudio.h>
#include <FileWvIn.h>
#include "frequencydomaindisplay.h"
#include "recordedsounddisplay.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// function delclarations TODO: REMOVE
// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples once the buffer has been filled or is empty initially.
// tickSine creates a buffer for sine, tickfile creates a buffer for an audio file
int tickSine( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer );

int tickFile( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData );

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawWaveFromFile(QString file);

    //Adds the controller which manages interactions on the main window

private:
    //Setup functions
    //Called upon initialization
    void setup_STK();
    void setup_FrequencyBox(int initialFrequency);


private slots:
    // Interaction Functions
    void on_FrequencySlider_valueChanged(int value);
    void on_playSineButton_clicked(bool);

    // Stops all sound currently playing
    void on_stopSound_clicked(bool);

private:
    Ui::MainWindow *ui;

    //RtAudio API variables
    RtAudio dac; // digital to analogue converter
    RtAudio::StreamParameters streamParameters;
    RtAudioFormat audioFormat;
    unsigned int bufferFrames; // size of buffer

    stk::FileWvIn input; // input files


    const float stkFrequency = 44100.0;

    int sineWaveFrequency = 440;
    stk::SineWave sineWave;

    //Generates a .wav file based on the content of sineWave
    //@param file: loction to store generated .wav file
    void generateSineWav(QString file);

    // plays a sine wave based on frequency
    void playSine();

    //plays any file
    void playFile(QString file);

};
#endif // MAINWINDOW_H
