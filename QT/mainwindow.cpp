#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setup_FrequencyBox(600);
}

void MainWindow::setup_FrequencyBox(int initialFrequency) {
    ui->FrequencySlider->setMinimum(20);
    ui->FrequencySlider->setMaximum(22050);
    ui->FrequencySlider->setSingleStep(100);
    ui->FrequencySlider->setValue(initialFrequency);
}

void MainWindow::on_pushButton_clicked(bool) {
    std::cout << "Lesss gooo" << std::endl;
}

void MainWindow::on_pushButton_2_clicked(bool) {
    std::cout << "Dumb af" << std::endl;
}

void MainWindow::on_FrequencySlider_valueChanged(int value) {
    ui->FrequencyLabel->setText(QString::number(value) + "Hz");
}

void MainWindow::drawWaveFromFile(QString file)
{
    ui->timeDomainInput->setSource(file);
    //ui->timeDomainInput->plot();
}

void MainWindow::on_playButton_clicked(bool)
{

    // Get current cursor position when it exists
    // If this following section is not loading the sound file
    // Ensure that you have the right working directory set under
    // Projects->Run->Working Directory
    QString currentDirectory = QDir::currentPath();
    //std::cout << "Play Button Pushed, currentDir =" << currentDirectory.toStdString() << std::endl;
    QString file = currentDirectory + "/ImperialMarch60.wav";
    drawWaveFromFile(file);
    //std::cout << "Play Button Finished" << std::endl;
}


MainWindow::~MainWindow()
{
    delete ui;
}
