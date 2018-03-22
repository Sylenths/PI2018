
#ifndef SINGLETON_SINGLETON_H
#define SINGLETON_SINGLETON_H

template <typename T>
class Singleton {
private:
    static T* instance;
public:
    static T* ObtenirInstance(){
        if(!instance)
            instance = new T();
        return instance;
    }
};
template <typename T>
T* Singleton<T>::instance = NULL;


#endif //SINGLETON_SINGLETON_H
