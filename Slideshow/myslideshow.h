#ifndef MYSLIDESHOW_H
#define MYSLIDESHOW_H
#include <QBasicTimer>
#include "subject.h"
#include <QStringList>
#include <algorithm>
#include <QtCore/QString>
#include <QLinkedList>
#include <QTimer>
#include <QDir>


class MySlideshow : public QObject, public Subject
{
    Q_OBJECT
public:
 MySlideshow();
 ~MySlideshow();
 void registerObserver(Observer* o) override;
 void removeObserver(Observer* o) override;
 void notifyObservers(std::string action) const override;
 void notifyErrors(std::string action) const;
 QStringList& resizeList(QStringList imagesList);

 void openFolder(QWidget *qw);
 void setPaths(QString dirPath);
 void goForward();
 void goBack();
 void start(QObject *qw);
 void pause();
 void stop();
 void changeInterval(int t);
 QStringList setMaxImagesList(QStringList imagesList);

 int foo(int i);

 void setFolderPath(const QString path);
 const QString getFolderPath() const;

 void setFilters(const QString filter);
 const QStringList getFilters() const;

 void setImagesPath(QString imgPath);
 const QStringList getImagesPaths() const;

 void setIntervalTimer(int val);
 const int getIntervalTimer() const;

 void setTimer(QTimer* tim);
 const QTimer& getTimer() const;

 void setCurrentImg(int currentImg);
 const int getCurrentImg() const;



private:

 std::list<Observer* > observers;
 QStringList filters {"*.jpg", "*.jpeg", "*.png", ".gif"};
 QString folderPath;
 QStringList imagesPaths;
 int maxImagesListSize;
 int currentImg = 0;
 QTimer *timer;
 int defaultIntervalTimer;
 int intervalTimer;

};

#endif // MYSLIDESHOW_H
