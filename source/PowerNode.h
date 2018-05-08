#ifndef POWERNODE_H
#define POWERNODE_H
#include "Model.h"
#include "includes.h"


class PowerNode : public Model {
protected:
    int key;
    int indice;

public:
    PowerNode(const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : Model(name, posx, posy, posz, textureID, rotHitBox, objFile) {
        this->indice = 9999;
    }

    void setIndice(int indice) {
        this->indice = indice;
    }

    int getIndice() {
        return indice;
    }

    void setKey(int key) {
        this->key = key;
    }

    int getKey() {
        return key;
    }






};

#endif
