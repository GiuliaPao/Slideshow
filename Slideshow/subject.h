#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
class Subject
{
public:

    virtual void registerObserver(Observer* o)= 0;
    virtual void removeObserver(Observer* o)=0;
    virtual void notifyObservers(std::string action) const =0;
protected:
    virtual ~Subject(){}

};

#endif // SUBJECT_H
