#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtMultimedia/QAudioInput>
#include <QBuffer>
#include <QMainWindow>
#include "external/ECE496-Backend/src/audioconfig.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    AudioConfig* audioConf = new AudioConfig;

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
