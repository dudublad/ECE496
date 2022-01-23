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
    setup_FrequencyBox(600);
    this->sine = audioSine();
}

void MainWindow::setup_FrequencyBox(int initialFrequency) {
    ui->FrequencySlider->setMinimum(20);
    ui->FrequencySlider->setMaximum(22050);
    ui->FrequencySlider->setSingleStep(100);
    ui->FrequencySlider->setValue(initialFrequency);
}

void MainWindow::on_FrequencySlider_valueChanged(int value) {
    ui->FrequencyLabel->setText(QString::number(value) + "Hz");
}

void MainWindow::drawWaveFromFile(QString file)
{
    ui->timeDomainInput->setSource(file);
    ui->timeDomainInput->plot();
}

void MainWindow::on_playSineButton_clicked(bool) {

    QString currentDirectory = QDir::currentPath();
    QString file = currentDirectory + "/audio_files/gen_sine.wav";

//    Clear the graph so that generateSineWave() is not
//    Accessing the same file
//    TODO: Better method for this
    drawWaveFromFile("");
    this->sine.setFilePath(file);
    this->sine.generateSine();
    drawWaveFromFile(file);
    sine.playSine();
}

void MainWindow::on_stopSound_clicked(bool){
    audio.closeStream();
}

MainWindow::~MainWindow()
{
    delete ui;
}
