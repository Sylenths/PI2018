//
// Created by etudiant on 18-04-10.
//

#ifndef SOURCE_SIMPARAMETER_H
#define SOURCE_SIMPARAMETER_H
template <typename T>
class SIMparameter{
private:
    std::string name;
    T data;
public:
    T getData(){
        return data;
    }
};


#endif //SOURCE_SIMPARAMETER_H
