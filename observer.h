#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>

class Observer
{
public:
    virtual void update(std::string action)=0;
    virtual void error(std::string action)=0;
protected:
    virtual ~Observer(){}

};

#endif // OBSERVER_H

