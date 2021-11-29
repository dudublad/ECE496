#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtMultimedia/QAudioInput>
#include <QBuffer>
#include "qcustomplot.h"
#include <QMainWindow>
#include "timedomain.h"
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
    void setup_FrequencyBox(int initialFrequency);


private slots:
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked(bool checked);

    // Interaction Functions
    void on_FrequencySlider_valueChanged(int value);
    void on_playButton_clicked(bool);

private:
    Ui::MainWindow *ui;
    TimeDomain *timeDomainInput;
};
#endif // MAINWINDOW_H
