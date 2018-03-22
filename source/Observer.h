#ifndef OBSERVER_H
#define OBSERVER_H

template <typename  T>
class Observer {
public:
    virtual void notification(T arg) = 0;

};


#endif
