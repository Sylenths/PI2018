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

//Movement in coordinate system units per second
#define MOVEMENT_SPEED 0.1

#define WINDOW_HEIGHT_F 720.
#define WINDOW_WIDTH_F 1280.
#define WINDOW_HEIGHT_I 720
#define WINDOW_WIDTH_I 1280
#define CAMERA_VROTLIMIT 718
#define CAMERA_FOV_F 90.
#define CAMERA_2FOV_F 180.




class Camera : public Observer<SDL_Event*> {
private:
	Matrix view;
	Vector position;
	Vector target;
	Vector up;

	int vMouseMotion;

public:

	/// Calcule l'angle du regard par rapport à la verticale (intervalle ]0, 180[ ; 0 est vers le haut / les y+.)
	/// \return Angle.
	double getVerticalRotationAngle(){
		return radtodeg(std::acos(Vector(0, 1, 0) * ((target - position).normalize())));
	}

	/// Calcule l'angle du regard par rapport à l'horizontale (intervalle ]90, -90[ ; 0 est horizontal et les négatifs sont vers le bas / les y-.)
	/// \return Angle.
	double getHorizontalAngle(){
		double angle = getVerticalRotationAngle();

		if(angle <= CAMERA_FOV_F){
			angle = CAMERA_FOV_F - angle;
		}
		else {
			angle = -CAMERA_FOV_F + (CAMERA_2FOV_F - angle); // plus grand que 90 degrés
		}
		return angle;
	}

	/// Constructeur
	/// \param position Position de la caméra.
	/// \param target Cible de la caméra.
	/// \param up Vecteur pointant vers le haut du monde.
	/// \param mode Mode de déplacement de la caméra.
	Camera(const Vector& position, const Vector& target, const Vector& up) {
		this->position = position;
		this->target = target;
		this->up = up;

		this->up.normalize();

		double angle = getHorizontalAngle();

		vMouseMotion = (int)(std::round(-angle / CAMERA_FOV_F * WINDOW_HEIGHT_I));
	}

	/// Charger la matrice de vue de la caméra.
	void loadViewMatrix() {
		Vector front = (target - position).normalize();
		Vector side = (front % up).normalize();
		up = (side % front).normalize();//correct the up vector
		view.loadView(front, side, up);
	}

	/// Notification de la caméra d'un événement d'appui de touche du clavier ou de déplacement de souris.
	/// \param event SDL_Event* contenant le déplacement de souris ou l'appui de la touche du clavier.
	void notification(SDL_Event* event) {

		if(event->type == SDL_MOUSEMOTION) {
			Matrix m;

			int yMove;

			if((vMouseMotion + event->motion.yrel) > CAMERA_VROTLIMIT) {
				yMove = CAMERA_VROTLIMIT - vMouseMotion;
			}
			else if((vMouseMotion + event->motion.yrel) < -CAMERA_VROTLIMIT) {
				yMove = -CAMERA_VROTLIMIT - vMouseMotion;
			}
			else {
				yMove = event->motion.yrel;
			}

			vMouseMotion += yMove;

			m.loadArbitraryRotation(position, Vector(0., 1., 0.), -(event->motion.xrel / WINDOW_WIDTH_F * CAMERA_FOV_F));
			target = m * target; // Horizontal camera rotation.

			m.loadYRotation(event->motion.xrel / WINDOW_WIDTH_F * CAMERA_FOV_F);
			up = m * up; // Up vector rotation.

			m.loadArbitraryRotation(position, ((target - position) % up).normalize(), -((double)yMove / WINDOW_HEIGHT_F * CAMERA_FOV_F));
			target = m * target; // Vertical camera rotation.

			loadViewMatrix();

			//std::cout << vMouseMotion << " -=- " << yMove << "-+-" << getVerticalRotationAngle()<< " /// " << getHorizontalAngle() << std::endl;
		}
		else {
			//Move position; arg has key pressed
			{
				//move camera and target in viewing direction
				Vector front = (target - position).normalize();

				switch(event->key.keysym.sym) {
					case SDLK_w: {
						front = front * MOVEMENT_SPEED;

						position = position + front;
						target = target + front;
					}
						break;

					case SDLK_a: {
						Vector side = (front % up) * MOVEMENT_SPEED;

						position = position - side;
						target = target - side;
					}
						break;

					case SDLK_s: {
						front = front * MOVEMENT_SPEED;

						position = position - front;
						target = target - front;
					}
						break;

					case SDLK_d: {
						Vector side = (front % up) * MOVEMENT_SPEED;

						position = position + side;
						target = target + side;
					}
						break;
					default:
						break;
				}
			}
			//todo: Eventually, make movement smoother by using MOVEMENT_SPEED * deltaTime, flags and handling multiple keys pressed.
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
