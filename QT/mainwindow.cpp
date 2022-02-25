#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Stk.h>
#include "FileWvOut.h"
#include "../external/ECE496-Backend/src/wave.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete audioConf;
}
