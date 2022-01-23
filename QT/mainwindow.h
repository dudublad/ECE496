#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtMultimedia/QAudioInput>
#include <QBuffer>
#include "qcustomplot.h"
#include <QMainWindow>
#include "timedomain.h"
#include "frequencydomaindisplay.h"
#include "recordedsounddisplay.h"
#include "external/ECE496-Backend/src/audiosine.h"

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

private:
    //Setup functions
    //Called upon initialization
    void setup_FrequencyBox(int initialFrequency);
    audioSine sine;

private slots:
    // Interaction Functions
    void on_FrequencySlider_valueChanged(int value);
    void on_playSineButton_clicked(bool);

    // Stops all sound currently playing
    void on_stopSound_clicked(bool);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
