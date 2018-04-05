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

#define CAMERAMODE_RAIL 0
#define CAMERAMODE_FIRSTPERSON 1
#define CAMERAMODE_FLY 2

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
	char cameraMode;

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
			angle = -CAMERA_FOV_F + (CAMERA_2FOV_F - angle);
		}
		return angle;
	}

	/// Constructeur
	/// \param position Position de la caméra.
	/// \param target Cible de la caméra.
	/// \param up Vecteur pointant vers le haut du monde.
	/// \param mode Mode de déplacement de la caméra.
	Camera(const Vector& position, const Vector& target, const Vector& up, const char mode) {
		this->position = position;
		this->target = target;
		this->up = up;

		this->up.normalize();

		double angle = getHorizontalAngle();

		vMouseMotion = (int)(std::round(-angle / CAMERA_FOV_F * WINDOW_HEIGHT_I));

		cameraMode = mode;
	}

	/// Sélection du mode de déplacement de la caméra.
	void setMode(char cameraMode) {
		this->cameraMode = cameraMode;
	}

	/// Charger la matrice de vue de la caméra.
	void loadViewMatrix() {
		Vector front = (target - position).normalize();
		Vector side = (front % up).normalize();
		up = (side % front).normalize();//correct the up vector
		view.loadView(front, side, up);
	}

	/// Notification de la caméra d'un événement d'appui de touche du clavier ou de déplacement de souris.
	/// \param arg SDL_Event* contenant le déplacement de souris ou l'appui de la touche du clavier.
	void notification(SDL_Event* arg) {

		if(arg->type == SDL_MOUSEMOTION) {
			Matrix m;

			int yMove;

			if((vMouseMotion + arg->motion.yrel) > CAMERA_VROTLIMIT) {
				yMove = CAMERA_VROTLIMIT - vMouseMotion;
			}
			else if((vMouseMotion + arg->motion.yrel) < -CAMERA_VROTLIMIT) {
				yMove = -CAMERA_VROTLIMIT - vMouseMotion;
			}
			else {
				yMove = arg->motion.yrel;
			}

			vMouseMotion += yMove;

			m.loadArbitraryRotation(position, Vector(0., 1., 0.), -(arg->motion.xrel / WINDOW_WIDTH_F * CAMERA_FOV_F));
			target = m * target; // Horizontal camera rotation.

			m.loadYRotation(arg->motion.xrel / WINDOW_WIDTH_F * CAMERA_FOV_F);
			up = m * up; // Up vector rotation.

			m.loadArbitraryRotation(position, ((target - position) % up).normalize(), -((double)yMove / WINDOW_HEIGHT_F * CAMERA_FOV_F));
			target = m * target; // Vertical camera rotation.

			loadViewMatrix();

			std::cout << vMouseMotion << " -=- " << yMove << "-+-" << getVerticalRotationAngle()<< " /// " << getHorizontalAngle() << std::endl;
		} else {
			//Move position; arg has key pressed
			//todo: Eventually, make movement smoother by using MOVEMENT_SPEED * deltaTime, flags and handling multiple keys pressed.
			switch(cameraMode) {
				case CAMERAMODE_RAIL: {
					switch(arg->key.keysym.sym) {

						case SDLK_w:
							position.z = position.z - MOVEMENT_SPEED;
							target.z = target.z - MOVEMENT_SPEED;
							break;

						case SDLK_a:
							position.x = position.x - MOVEMENT_SPEED;
							target.x = target.x - MOVEMENT_SPEED;
							break;

						case SDLK_s:
							position.z = position.z + MOVEMENT_SPEED;
							target.z = target.z + MOVEMENT_SPEED;
							break;

						case SDLK_d:
							position.x = position.x + MOVEMENT_SPEED;
							target.x = target.x + MOVEMENT_SPEED;
							break;

						default:
							break;
					}
				}
					//Move camera and target in the same direction, relative to world coordinate system.
					break;
				case CAMERAMODE_FIRSTPERSON: {
					//Move camera and target in horizontal viewing direction.
					Vector gndDir = (target - position);
					gndDir.y = 0.;
					gndDir.normalize();

					switch(arg->key.keysym.sym) {
						case SDLK_w: {
							gndDir = gndDir * MOVEMENT_SPEED;

							position = position + gndDir;
							target = target + gndDir;
						}
							break;

						case SDLK_a: {
							Vector side = (gndDir % Vector(0., 1., 0.)).normalize() * MOVEMENT_SPEED;

							position = position - side;
							target = target - side;
						}
							break;

						case SDLK_s: {
							gndDir = gndDir * MOVEMENT_SPEED;

							position = position - gndDir;
							target = target - gndDir;
						}
							break;

						case SDLK_d: {
							Vector side = (gndDir % Vector(0., 1., 0.)).normalize() * MOVEMENT_SPEED;

							position = position + side;
							target = target + side;
						}
							break;
						default:
							break;
					}
				}
					break;
				case CAMERAMODE_FLY: {
					//move camera and target in viewing direction
					Vector front = (target - position).normalize();

					switch(arg->key.keysym.sym) {
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

					break;
				default:
					break;
			}
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
