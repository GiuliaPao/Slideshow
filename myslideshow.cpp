#include "myslideshow.h"
#include <iostream>
#include <QDir>
#include <QPixmap>
#include <QStringList>
#include <QFileDialog>



MySlideshow::MySlideshow()
        : folderPath("../Slideshow/images"), timer(nullptr), defaultIntervalTimer(2000), maxImagesListSize(4) {
    intervalTimer = defaultIntervalTimer;
    imagesPaths.reserve(maxImagesListSize);
}

MySlideshow::~MySlideshow() {
    if(timer){
        delete timer;
    }
}

/*REGISTER REMOVE AND NOTIFY OBSERVER*/
void MySlideshow::registerObserver(Observer *obs) {
    observers.push_back(obs);
}

void MySlideshow::removeObserver(Observer *obs) {
    observers.remove(obs);
}

void MySlideshow::notifyObservers(std::string action) const {

    for (auto it = observers.begin(); it != observers.end(); ++it) {
        (*it)->update(action);
    }

}


void MySlideshow::notifyErrors(std::string action) const {

    for (auto it = observers.begin(); it != observers.end(); ++it) {
        (*it)->error(action);
    }

}
/*OTHER METHODS*/
/*OPEN FILES*/
void MySlideshow::openFolder(QWidget *qw) {
    QString path;
    path = QFileDialog::getExistingDirectory(qw, "Choose directory", getFolderPath()); //posso passare come ultimo parametro un "Option", tra cui quella di mostrare solo le cartelle.
    // Il comportamento di default sarebbe mostrare anche i file ma su Windows non funge. daje
    if(path != ""){
        setFolderPath(path);
        setPaths(path);
    }else{
        this->notifyErrors("directoryPath");
    }

}

void MySlideshow::setPaths(QString dirPath){
    QDir dir(dirPath);
    imagesPaths = dir.entryList(getFilters());
    if (!imagesPaths.empty()) {
        //imagesPaths = setMaxImagesList(imagesPaths);
        if(imagesPaths.size()>maxImagesListSize)
            imagesPaths = resizeList(imagesPaths);
        setCurrentImg(0);
        notifyObservers("open");
    }
}

QStringList& MySlideshow::resizeList(QStringList imagesList){
    QStringList* newImagesPaths = new QStringList();
    for(int i = 0; i<maxImagesListSize; i++)
        newImagesPaths->append(imagesList.at(i));
    return *newImagesPaths;

}


/*MOVE*/
void MySlideshow::goForward() {
    if (currentImg >= imagesPaths.size() - 1) {
        currentImg = 0;
    } else {
        currentImg++;
    }
    notifyObservers("forward");
}

void MySlideshow::goBack() {
    if (currentImg <= 0) {
        currentImg = imagesPaths.size() - 1;
    } else {
        currentImg--;
    }
    notifyObservers("back");

}

void MySlideshow::start(QObject *qw) {
    if (!timer) {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), qw, SLOT(on_pushButton_forward_clicked()));
        timer->setInterval(defaultIntervalTimer);
        timer->start(timer->interval());
    }else{
        timer->start(timer->interval());
    }
}

void MySlideshow::pause(){
    if(timer){
        timer->stop();
    }
}

void MySlideshow::stop(){
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }

}

void MySlideshow::changeInterval(int t) {
    if (timer) {
        intervalTimer = t * 100;
        timer->setInterval(intervalTimer);
    }
}


/*GETTER AND SETTER FILTERS*/
const QStringList MySlideshow::getFilters() const {
    return filters;
}

void MySlideshow::setFilters(const QString filter) {
    filters.push_back(filter);
}

/*GETTER AND SETTER FOLDER PATH*/
const QString MySlideshow::getFolderPath() const {
    return folderPath;
}

void MySlideshow::setFolderPath(const QString path) {
    folderPath = path;
}

/*GETTER AND SETTER IMAGES PATHS*/
const QStringList MySlideshow::getImagesPaths() const {
    return imagesPaths;
}

void MySlideshow::setImagesPath(QString imgPath) {
    if(imagesPaths.size()<maxImagesListSize)
        imagesPaths.push_back(imgPath);
}

/*GETTER AND SETTER CURRENT IMG INDEX*/
const int MySlideshow::getCurrentImg() const {
    return currentImg;
}

void MySlideshow::setCurrentImg(int curImg) {
    MySlideshow::currentImg = curImg;
}

void MySlideshow::setIntervalTimer(int val){
    intervalTimer = val;
}
const int MySlideshow::getIntervalTimer() const{
    return intervalTimer;
}

void MySlideshow::setTimer(QTimer* tim){
    timer = tim;
}
const QTimer& MySlideshow::getTimer() const{
    return *timer;
}


