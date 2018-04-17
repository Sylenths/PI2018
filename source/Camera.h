/// \brief Représentation d'une caméra.
/// \details Caméra dont le déplacement est contrôlable par l'utilisateur avec les touches WASD et la souris.
/// \author Samuel Labelle
/// \date 4 Avril 2018
/// \version 0.2
/// \warning position et target doivent être différents et non-colinéaires sur les y. Champ de vision de 90 degrés.
/// \bug Mouvement par déplacement sucessif fixes dépendant du taux de rafraichissement des touches du clavier.

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Observer.h"
#include "Matrix.h"
#include "Vector.h"

#define CAMERA_MOVEMENTSPEED 1
#define CAMERA_ROTATIONSPEED 3

#define CAMERA_VERTICAL_LIMIT 0.1

#define CAMERA_MOVE_FRONT 1
#define CAMERA_MOVE_BACK 2
#define CAMERA_MOVE_LEFT 3
#define CAMERA_MOVE_RIGHT 4

#define WINDOW_HEIGHT_F 720.
#define WINDOW_WIDTH_F 1280.
#define WINDOW_HEIGHT_I 720
#define WINDOW_WIDTH_I 1280
#define CAMERA_VROTLIMIT 718
#define CAMERA_FOV_F 90.
#define CAMERA_2FOV_F 180.


class Camera{
private:
    Matrix view;
    Vector position;
    Vector target;
    Vector up;
	Vector front;
    bool mLeft, mRight, mFront, mBack;

    int vMouseMotion;

public:

    /// Calcule l'angle du regard par rapport à l'horizontale (intervalle ]90, -90[ ; 0 est horizontal et les négatifs sont vers le bas / les y-.)
    /// \return Angle.
    double getHorizontalAngle(){
        double angle = radtodeg(std::acos(up * ((target - position).normalize())));

        if(angle <= CAMERA_FOV_F){
            angle = CAMERA_FOV_F - angle;
        }
        else {
            angle = -CAMERA_FOV_F + (CAMERA_2FOV_F - angle); // plus grand que 90 degrés
        }
        return angle;
    }

    /// Accéder au vecteur unitaire pointant dans la direction où regarde la caméra.
    /// \return Vecteur unitaire.
    Vector getFront(){
        return front;
    }

    /// Constructeur
    /// \param position Position de la caméra.
    /// \param target Cible de la caméra.
    /// \param up Vecteur pointant vers le haut du monde.
    Camera(const Vector& position, const Vector& target, Vector up = Vector(0., 1., 0.)) {
        this->position = position;
        this->target = target;
        front = (target - position).normalize();

        this->up = up.normalize();

        vMouseMotion = (int)(std::round(-getHorizontalAngle() / CAMERA_FOV_F * WINDOW_HEIGHT_I));

        mLeft = mRight = mFront = mBack = false;
    }

    /// Charger la matrice de vue de la caméra.
    void loadViewMatrix() {
        front = (target - position).normalize();
        Vector side = (front % up).normalize();
        view.loadView(front, side, (side % front).normalize()/*This is camera local up vector*/);
    }

    /// Mettre à jour la position de la caméra.
    /// \param deltaTime Temps écoulé.
    void update(double deltaTime){
        //move camera and target in viewing direction
        if(mFront || mBack || mLeft || mRight) {
            front = (target - position).normalize();
            double moveAmplitude = CAMERA_MOVEMENTSPEED * deltaTime;
            Vector movement;

            if(mFront || mBack) {

                movement = front * moveAmplitude;

                if(mFront) {
                    position = position + movement;
                    target = target + movement;
                }
                else {
                    position = position - movement;
                    target = target - movement;
                }

	            // See if we are through the ground / height limit...
	            if(position.y < CAMERA_VERTICAL_LIMIT ) {
		            Vector push = Vector(0.0, CAMERA_VERTICAL_LIMIT - position.y, 0.0);
		            position = position + push;
		            target = target + push;
	            }
            }
            if(mLeft || mRight) {
                movement = (front % up) * moveAmplitude;

                if(mLeft) {
                    position = position - movement;
                    target = target - movement;
                }
                else {
                    position = position + movement;
                    target = target + movement;
                }
            }
        }
    }

	/// Tourner la caméra.
	/// \param relativeYMotion Mouvement relatif de la souris en Y (pixels).
	/// \param relativeXMotion Mouvement relatif de la souris en X (pixels).
    void rotateView(int relativeXMotion, int relativeYMotion) {
        Matrix m;

        int yMove;

        if((vMouseMotion + relativeYMotion) > CAMERA_VROTLIMIT) {
            yMove = CAMERA_VROTLIMIT - vMouseMotion;
        }
        else if((vMouseMotion + relativeYMotion) < -CAMERA_VROTLIMIT) {
            yMove = -CAMERA_VROTLIMIT - vMouseMotion;
        }
        else {
            yMove = relativeYMotion;
        }

        vMouseMotion += yMove;

        m.loadArbitraryRotation(position, up,  -(relativeXMotion / WINDOW_WIDTH_F * CAMERA_FOV_F) * CAMERA_ROTATIONSPEED);
        target = m * target; // Horizontal camera rotation.

        m.loadArbitraryRotation(position, ((target - position) %  up).normalize(), -((double)yMove / WINDOW_HEIGHT_F * CAMERA_FOV_F));
        target = m * target; // Vertical camera rotation.

        loadViewMatrix();

    }

	/// Initie un mouvemnt dans une direction.
	/// \param move Direction du mouvement.
	void startMove(char move){
		switch(move){
			case CAMERA_MOVE_FRONT:
				mFront = true;
				mBack = false;
				break;
			case CAMERA_MOVE_BACK:
				mBack = true;
				mFront = false;
				break;
			case CAMERA_MOVE_LEFT:
				mLeft = true;
				mRight = false;
				break;
			case CAMERA_MOVE_RIGHT:
				mRight = true;
				mLeft = false;
				break;
			default:
				break;
		}
	}

	/// Interrompt le mouvement dans une direction.
	/// \param move Direction du mouvement.
	void stopMove(char move){
		switch(move){
			case CAMERA_MOVE_FRONT:
				mFront = false;
				break;
			case CAMERA_MOVE_BACK:
				mBack = false;
				break;
			case CAMERA_MOVE_LEFT:
				mLeft = false;
				break;
			case CAMERA_MOVE_RIGHT:
				mRight = false;
				break;
			default:
				break;
		}
	}

    /// Applique la matrice de vue de la caméra au contexte OpenGL.
    void applyViewMatrix() {
        glLoadIdentity();
        glMultMatrixd(view.matrix);
        glTranslated(-position.x, -position.y, -position.z);
    }

};

#endif //CAMERA_H
