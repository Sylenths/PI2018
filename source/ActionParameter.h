#ifndef SOURCE_SIMPARAMETER_H
#define SOURCE_SIMPARAMETER_H


#define SIMINT 1
#define SIMDOUBLE 2

class ActionParameter{
private:
    std::string name;

public:
    ActionParameter(std::string name){
        this->name = name;
    }


    virtual int getType() = 0;
};

#endif
