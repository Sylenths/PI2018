
#ifndef SOURCE_IMAGE2D_H
#define SOURCE_IMAGE2D_H

#include "Model.h"
#include "Matrix.h"

class Image2D : public Model {
public:
    Image2D(std::string textureName, unsigned int x, unsigned int y, unsigned int z, double width, double height) : Model(textureName) {

        vertexCount = normalCount = texCount = 6;

        vertices = new double[vertexCount * 3] {

                0.0 + x  , 0.0 + y   , 0.0, //P1T1F1
                width + x, height + y, 0.0, //P2T1F1
                0.0 + x  , height + y, 0.0, //P3T1F1

                0.0 + x  , 0.0 + y   , 0.0, //P1T2F1
                width + x, 0.0 + y   , 0.0, //P2T2F1
                width + x, height + y, 0.0, //P3T2F1
        };

        normals = new double[normalCount * 3] {
            0.0, 0.0, 1.0, //P1T1F1
            0.0, 0.0, 1.0, //P2T1F1
            0.0, 0.0, 1.0, //P3T1F1

            0.0, 0.0, 1.0, //P1T2F1
            0.0, 0.0, 1.0, //P2T2F1
            0.0, 0.0, 1.0, //P3T2F1
        };

        texCoords = new double[texCount * 2] {
                0.0,0.0,
                1.0,1.0,
                0.0,1.0,
                0.0,0.0,
                1.0,0.0,
                1.0,1.0,
        };
    }

    void notify(SDL_Event* sdlEvent) {}


};


#endif
