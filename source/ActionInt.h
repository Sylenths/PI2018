//
// Created by etudiant on 18-04-12.
//

#ifndef SOURCE_ACTIONINT_H
#define SOURCE_ACTIONINT_H

class ActionInt : public ActionParameter{
private:
    int data;
public:

    ActionInt(int data, std::string name) : ActionParameter(name){
        
    }
    int getData(){
        return data;
    }

};
#endif //SOURCE_ACTIONINT_H
