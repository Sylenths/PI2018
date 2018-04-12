#ifndef SOURCE_SIMPARAMETER_H
#define SOURCE_SIMPARAMETER_H

class ActionParameter{
private:
    std::string name;

public:
    ActionParameter(std::string name){
        this->name = name;
    }

    virtual std::string getType() = 0;
};

#endif
