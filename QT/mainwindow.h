#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtMultimedia/QAudioInput>
#include <QBuffer>
#include "qcustomplot.h"
#include <QMainWindow>
#include "timedomain.h"
#include <SineWave.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked(bool checked);

    // Interaction Functions
    void on_FrequencySlider_valueChanged(int value);
    void on_playButton_clicked(bool);
    void on_playSineButton_clicked(bool);

private:
    Ui::MainWindow *ui;
    TimeDomain *timeDomainInput;

    const float stkFrequency = 44100.0;

    int sineWaveFrequency = 440;
    stk::SineWave sineWave;

    //Generates a .wav file based on the content of sineWave
    //@param file: loction to store generated .wav file
    void generateSineWav(QString file);
};
#endif // MAINWINDOW_H
