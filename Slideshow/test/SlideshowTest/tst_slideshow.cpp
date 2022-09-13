#include <QtTest>
#include <QtWidgets>
#include <QCoreApplication>
#include <iostream>
#include "../../myslideshow.h"

// add necessary includes here

class slideshow : public QObject
{
    Q_OBJECT

public:
    slideshow();
    ~slideshow();
private:
    MySlideshow* ms;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_forward();
    void test_back();
    void test_interval_timer();
    void test_image_list_size();

};

slideshow::slideshow()
{

}

slideshow::~slideshow()
{

}

void slideshow::initTestCase()
{
    ms = new MySlideshow();
    QString defaultPath = ms->getFolderPath();

    ms->setImagesPath("image1");
    ms->setImagesPath("image2");
    ms->setImagesPath("image3");
    ms->setImagesPath("image4");
    ms->setImagesPath("image5");

}

void slideshow::cleanupTestCase()
{
    delete ms;
}

void slideshow::test_forward()
{
    ms->goForward();
    QCOMPARE(ms->getCurrentImg(), 1);
}

void slideshow::test_back()
{
    ms->goBack();
    ms->goBack();
    QCOMPARE(ms->getCurrentImg(), 3);
}

void slideshow::test_interval_timer()
{
    QTimer* tim = new QTimer;
    ms->setTimer(tim);
    ms->changeInterval(30);
    QCOMPARE(ms->getIntervalTimer(), 3000);
}

void slideshow::test_image_list_size()
{
    QCOMPARE(ms->getImagesPaths().size(), 4);
}

QTEST_MAIN(slideshow)

#include "tst_slideshow.moc"
