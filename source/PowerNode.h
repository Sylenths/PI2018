#ifndef POWERNODE_H
#define POWERNODE_H
#include "Model.h"
#include "includes.h"


class PowerNode : public Model {
protected:
    int key;
    int indice;
    Model* sphere;

public:
    PowerNode(const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : Model(name, posx, posy, posz, textureID, rotHitBox, objFile) {
        this->indice = 9999;
        sphere = new Model("", realCenter.x, realCenter.y, realCenter.z, EntityManager::get<Texture2d*>("Blue")->ID, false,"../../models/obj/sphere.obj");
        sphere->setTexture("red",EntityManager::get<Texture2d*>("Red")->ID);
        sphere->setTexture("green",EntityManager::get<Texture2d*>("Green")->ID);
    }

    void setIndice(int indice) {
        this->indice = indice;

    }

    int getIndice() {
        return indice;
    }

    void setKey(int key) {
        this->key = key;
        if(key <= 0)
            sphere->setTexture();
    }

    int getKey() {
        return key;
    }

    void drawOverlay() {
        sphere->draw();
    }






};

#endif
