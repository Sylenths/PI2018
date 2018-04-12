//
// Created by etudiant on 18-04-10.
//

#ifndef SOURCE_SIMPARAMETER_H
#define SOURCE_SIMPARAMETER_H
class Actionparameter{
private:
    std::string name;
public:
    Actionparameter(std::string name){
        this->name = name;
    }
    template <typename T>
    virtual T getData() = 0;
};


#endif //SOURCE_SIMPARAMETER_H
