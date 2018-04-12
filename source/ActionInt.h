#ifndef SOURCE_ACTIONINT_H
#define SOURCE_ACTIONINT_H

class ActionInt : public ActionParameter{
private:
    int data;

public:
    ActionInt(std::string name, int data) : ActionParameter(name) {
        this->data = data;
    }

    int getType() {
        return SIMINT;
    }

    ActionInt(int data, std::string name) : ActionParameter(name){

    }
    int getData(){
        return data;
    }

};

#endif
