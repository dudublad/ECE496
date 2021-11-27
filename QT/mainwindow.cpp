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
    ui->FrequencySlider->setMinimum(300);
    ui->FrequencySlider->setMaximum(2000);
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

MainWindow::~MainWindow()
{
    delete ui;
}

