#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "observer.h"
#include "myslideshow.h"
#include <list>
#include <algorithm>
#include <QPixmap>
#include <iostream>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT
public:
    MainWindow(MySlideshow* s, QWidget *parent = nullptr);
    ~MainWindow();

    void update(std::string action) override;
    void error(std::string action) override;

    void updateOnOpen();
    void updateOnForward();
    void updateOnBack();
    void updateOnStart();
    void updateOnPause();
    void resetSpinbox();


private slots:
     void on_actionOpen_triggered();

     void on_pushButton_forward_clicked();

     void on_pushButton_back_clicked();

     void on_pushButton_start_clicked();

     void on_pushButton_pause_clicked();

     void enableButtons(bool value);

     void showImage(const QString& filePath);

     void on_spinBox_valueChanged(int arg1);

     void on_pushButton_stop_clicked();

private:
    Ui::MainWindow *ui;
    MySlideshow* slideshow;
    QStringList imagesPaths;
    bool btnActivation;
    int currentImg;
};
#endif // MAINWINDOW_H
