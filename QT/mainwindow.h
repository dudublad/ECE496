#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //Setup functions
    //Called upon initialization
    void setup_FrequencyBox(int initialFrequency);

private slots:
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked(bool checked);

    void on_FrequencySlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
