#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QAction>
#include <QFileDialog>
#include <QImageReader>
#include <QList>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QDir>

MainWindow::MainWindow(MySlideshow *s, QWidget *parent)
        : QMainWindow(parent), slideshow(s), ui(new Ui::MainWindow), btnActivation(false) {
    slideshow->registerObserver(this);
    ui->setupUi(this);
    enableButtons(btnActivation);
}

MainWindow::~MainWindow() {
    on_pushButton_pause_clicked();
    slideshow->removeObserver(this);
    delete ui;
}

void MainWindow::update(std::string action) {

    if (action == "open") {
        updateOnOpen();
    } else if (action == "forward") {
        updateOnForward();
    } else if (action == "back") {
        updateOnBack();
    } else if (action == "error");
}

void MainWindow::on_actionOpen_triggered() {
    slideshow->openFolder(this);
}

void MainWindow::updateOnOpen() {
    imagesPaths = slideshow->getImagesPaths();
    currentImg = slideshow->getCurrentImg();
    showImage(imagesPaths[currentImg]);
    btnActivation = true;
    enableButtons(btnActivation);
}


void MainWindow::on_pushButton_forward_clicked() {
    slideshow->goForward();

}

void MainWindow::updateOnForward() {
    currentImg = slideshow->getCurrentImg();
    showImage(imagesPaths[currentImg]);
}


void MainWindow::on_pushButton_back_clicked() {
    slideshow->goBack();
}

void MainWindow::updateOnBack() {
    currentImg = slideshow->getCurrentImg();
    showImage(imagesPaths[currentImg]);
}

void MainWindow::on_pushButton_start_clicked() {
    slideshow->start(this);

}

void MainWindow::on_pushButton_pause_clicked() {
    slideshow->pause();
}

void MainWindow::on_pushButton_stop_clicked()
{
    slideshow->stop();
    resetSpinbox();
}

void MainWindow::on_spinBox_valueChanged(int t) {

    slideshow->changeInterval(t);

}

void MainWindow::showImage(const QString &filePath) {

    QString currentPath = slideshow->getFolderPath();
    int w = ui->label_images->width();
    int h = ui->label_images->height();
    QPixmap img = QPixmap(currentPath + "/" + filePath);
    ui->label_images->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::resetSpinbox(){
    ui->spinBox->setValue(20);
}

void MainWindow::enableButtons(bool value) {
    ui->pushButton_back->setEnabled(btnActivation);
    ui->pushButton_forward->setEnabled(btnActivation);
    ui->pushButton_pause->setEnabled(btnActivation);
    ui->pushButton_start->setEnabled(btnActivation);
    ui->pushButton_stop->setEnabled(btnActivation);
    ui->spinBox->setEnabled(btnActivation);
}


void MainWindow::error(std::string action){
    if(action == "directoryPath"){
        ui->label_images->setText("NO DIRECTORY OPENED, TRY AGAIN");
    }
}


