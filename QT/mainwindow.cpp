#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_pushButton_clicked(bool checked) {
    std::cout << "Lesss gooo" << std::endl;
}

void MainWindow::on_pushButton_2_clicked(bool checked) {
    std::cout << "Dumb af" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

