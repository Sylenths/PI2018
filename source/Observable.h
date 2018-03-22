#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"
#include <list>

template <typename T>
class Observable {
private:
    std::list<Observer<T>*> observers;

public:
    void suscribe(Observer<T>* observer){
        observers.push_back(observer);
    }

    void notify(T arg){
        typename std::list<Observer<T>*>::iterator it = observers.begin();
        for (int i = 0; i <observers.size() ; ++i) {
            (*it++)->notification(arg);
        }

        /*
         * for(auto it : observers*)
         * it->notification;
         */
    }
};


#endif
