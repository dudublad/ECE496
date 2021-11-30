#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Stk.h>
#include "FileWvOut.h"

#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_STK();
    setup_FrequencyBox(600);
}

void MainWindow::setup_STK() {
    stk::Stk::setSampleRate(stkFrequency);
}

void MainWindow::setup_FrequencyBox(int initialFrequency) {
    ui->FrequencySlider->setMinimum(20);
    ui->FrequencySlider->setMaximum(22050);
    ui->FrequencySlider->setSingleStep(100);
    ui->FrequencySlider->setValue(initialFrequency);
}

void MainWindow::on_FrequencySlider_valueChanged(int value) {
    ui->FrequencyLabel->setText(QString::number(value) + "Hz");
    sineWaveFrequency = value;
}

void MainWindow::drawWaveFromFile(QString file)
{
    ui->timeDomainInput->setSource(file);
    ui->timeDomainInput->plot();
}

void MainWindow::on_playButton_clicked(bool)
{

    // Get current cursor position when it exists
    // If this following section is not loading the sound file
    // Ensure that you have the right working directory set under
    // Projects->Run->Working Directory
    QString currentDirectory = QDir::currentPath();
    //std::cout << "Play Button Pushed, currentDir =" << currentDirectory.toStdString() << std::endl;
    QString file = currentDirectory + "/audio_files/ImperialMarch60.wav";
    drawWaveFromFile(file);
    //std::cout << "Play Button Finished" << std::endl;
}

void MainWindow::on_playSineButton_clicked(bool) {

    QString currentDirectory = QDir::currentPath();
    QString file = currentDirectory + "/audio_files/gen_sine.wav";

    //Clear the graph so that generateSineWave() is not
    //Accessing the same file
    //TODO: Better method for this
    drawWaveFromFile("");

    generateSineWav(file);
    drawWaveFromFile(file);
}

void MainWindow::generateSineWav(QString file) {
    const float duration_secs = 0.1;
    const int numSamples = duration_secs * stkFrequency;

    stk::FileWvOut output;
    // Open a 16-bit, one-channel WAV formatted output file
    output.openFile(file.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);

    sineWave.reset();
    sineWave.setFrequency(sineWaveFrequency);
    for(int i = 0; i < numSamples; i++) {
        output.tick( sineWave.tick() );
    }

    output.closeFile();
}


MainWindow::~MainWindow()
{
    delete ui;
}
