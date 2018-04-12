//
// Created by etudiant on 18-04-12.
//

#ifndef SOURCE_ACTIONDOUBLE_H
#define SOURCE_ACTIONDOUBLE_H



class ActionDouble : public ActionParameter{
private:
    double data;

public:
    ActionDouble(std::string name, double data) : ActionParameter(name) {
        this->data = data;
    }

    double getType() {
        return SIMDOUBLE;
    }
    int getData(){
        return data;
    }

};
#endif //SOURCE_ACTIONDOUBLE_H
