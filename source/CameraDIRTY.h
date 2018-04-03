/// \brief La vision de l'utilisateur qui bougera dans la dimension 3D OpenGL semi-infini.
///
/// \details Cette vision bougera selon le mode qu'il a choisi. Il y a le mode chariot, première personne ou aérien que l'utilisateur pourra utiliser.
/// \author Taichen Li
/// \date inconnu
/// \version 0.1
/// \warning MANQUE D'OPTIMISATION MAJEUR DANS LA VISION DE LA CAMÉRA. Le tout peut être optimisé facilement.
/// \bug Problèmes connus: les mouvements en y sont limités et les déplacements sont étranges.

#ifndef SDLOGL_CAMERA_H
#define SDLOGL_CAMERA_H

#define freeview 0
#define premierepersonne 1
#define aerienne 2

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

#include "Matrix.h"
#include "Vector.h"
#include "Observer.h"

class CameraDIRTY : public Observer<SDL_Event*>{
private:
    Matrix view; ///< La matrice que OpenGL lit pour savoir les informations sur la caméra.
    Vector position; ///< La matrice view, mais avec ses composantes mises en évidence pour faciliter la manipulation. position est l'emplacement actuel de la caméra dans l'espace 3D OpenGL.
    Vector target; ///< La matrice view, mais avec ses composantes mises en évidence pour faciliter la manipulation. target est la direction que la caméra regarde.
    Vector up; ///< La matrice view, mais avec ses composantes mises en évidence pour faciliter la manipulation. up est le vecteur qui représente le haut de la caméra. Très utile quand il faut savoir où est la droite et la gauche de la caméra.

    Vector direction; ///< La matrice de direction
    Vector axis; ///< Le vecteur de l'axe de rotation

    Matrix transform;

    double degreeUpDown;
    unsigned int cameraMode;

    /// Cette méthode s'occupe du mouvement de la caméra en mode chariot.
    /// \param sdlEvent pour avoir au déplacement en x, y et z de la souris.

    void freecamera(SDL_Event* sdlEvent) {
        if(sdlEvent->type == SDL_KEYDOWN) {
            switch (sdlEvent->key.keysym.sym) {
                case SDLK_w:
                    position = position + direction.normalizeNPC();
                    break;
                case SDLK_s:
                    position = position - direction.normalizeNPC();
                    break;
                case SDLK_a:
                    position = position - (direction.normalizeNPCXZ() % Vector(0.0, 1.0, 0.0));
                    break;
                case SDLK_d:
                    position = position + (direction.normalizeNPCXZ() % Vector(0.0, 1.0, 0.0));
                    break;
                default:
                    break;
            }
            direction = target - position;
            loadViewMatrix();
        }

        /*
        if(sdlEvent->type == SDL_MOUSEMOTION) {
            if (sdlEvent->motion.xrel > 0) {
                transform.loadYrotation(0.01*sdlEvent->motion.xrel);
            }
            else {
                if (sdlEvent->motion.xrel < 0) {
                    transform.loadYrotation(0.01*sdlEvent->motion.xrel);
                }
            }
            direction = transform*direction;
            target = position + direction;
            loadViewMatrix();
        }
        */
        if(sdlEvent->type == SDL_MOUSEMOTION) {
            if (sdlEvent->motion.xrel != 0 || sdlEvent->motion.yrel != 0) {
                axis = {(double)sdlEvent->motion.xrel, (double)sdlEvent->motion.yrel, 0.0};
                axis = axis % direction;
                axis.normalize();
                transform.loadXYZrotation(0.01, axis, {0.0, 0.0, 0.0});
                direction = transform * direction;
                target = position + direction;
                loadViewMatrix();
            }
        }

    }

    /// Cette méthode s'occupe du mouvement de la caméra en mode première personne.
    /// \param sdlEvent pour avoir au déplacement en x, y et z de la souris.

public:
    CameraDIRTY(const Vector& position, const Vector& target, const Vector& up, unsigned int cameraMode) {
        this -> position = position;
        this -> target = target;
        this -> up = up;
        this -> up.normalize();

        direction = (this -> target) - (this -> position);

        this -> cameraMode = cameraMode;

        degreeUpDown = 0.0;
    }

    /// Mise à jour du vecteur up à partir du vecteur target et position

    void loadViewMatrix() {
        Vector front = (target - position).normalize();
        Vector side = (front % up).normalize();
        up = (side % front). normalize();
        view.loadView(front, side, up);
    }

    /// Application de la matrice view dans l'environnement OpenGL

    void applyViewMatrix() {
        glLoadIdentity();
        glMultMatrixd(view.matrix);
        glTranslated(-position.x, -position.y, -position.z);
    }

    /// Stimulation de l'un des modes de vu de la caméra
    /// \param sdlEvent Ce paramètre permet au programmeur de savoir quels sont les déplacements de souris.

    void notify(SDL_Event* sdlEvent) {

        switch(cameraMode) {
            case freeview:
                freecamera(sdlEvent);
                break;
            default:
                break;
        }

    }

};

#endif