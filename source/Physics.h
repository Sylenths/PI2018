/// \brief Classe de méthodes statiques pour les calculs de physique et de collisions.
/// \details
/// \author Samuel Labelle
/// \date 24 Avril 2018
/// \version 0.1
/// \warning Non extensivement testée
/// \bug Les calculs ne sont pas optimisés.

#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector.h"
#include "Matrix.h"
#include "Model.h"
#include "MathUtils.h"

#define PHYSICS_EPSILON 0.000001

namespace Physics {

	struct CollisionData {
		bool collided;
		Vector point;
		double ratio;
	};

	struct Triangle {
		Vector p1;
		Vector p2;
		Vector p3;
	};

	struct Vec2D {
		double x;
		double y;
	};

	struct FlatTriangle {
		Vec2D p1;
		Vec2D p2;
		Vec2D p3;
	};

}

class Physics{

public:

	/// Collisionne un segment et un triangle.
	/// \param segment Segment (Vecteur)
	/// \param tri Triangle.
	/// \param normal Normale du triangle.
	/// \return Structure de donnée contenant les résultats de la collision.
	static Physics::CollisionData collideVectorOnTri(Vector segment, Physics::Triangle tri, Vector normal){
		normal.normalize();
		segment.normalize();// Not sure if parts of the alo require non normalised segment vector...

		double dotp = normal * segment;

		if((PHYSICS_EPSILON > dotp) && (dotp > -PHYSICS_EPSILON))
			return {false};

		double ratio = ((normal * tri.p1) / (normal * segment));

		if(ratio > 1)
			return {false};

		Vector intersect(segment * ratio);

		Physics::FlatTriangle flatTri;
		Physics::Vec2D flatVec;

		if((normal.x > normal.y) && (normal.x > normal.z)){
			//remove x from tri
			flatTri = {{tri.p1.y, tri.p1.z}, {tri.p2.y, tri.p2.z}, {tri.p3.y, tri.p3.z}};
			flatVec = {intersect.y, intersect.z};
		}
		else if(normal.y > normal.z){
			//remove y from tri
			flatTri = {{tri.p1.x, tri.p1.z}, {tri.p2.x, tri.p2.z}, {tri.p3.x, tri.p3.z}};
			flatVec = {intersect.x, intersect.z};
		}
		else{
			//remove z from tri
			flatTri = {{tri.p1.x, tri.p1.y}, {tri.p2.x, tri.p2.y}, {tri.p3.x, tri.p3.y}};
			flatVec = {intersect.x, intersect.y};
		}

		bool b1 = signbit(det22(flatVec.x, flatVec.y, flatTri.p1.x, flatTri.p1.y));
		bool b2 = signbit(det22(flatVec.x, flatVec.y, flatTri.p2.x, flatTri.p2.y));
		bool b3 = signbit(det22(flatVec.x, flatVec.y, flatTri.p3.x, flatTri.p3.y));

		if(b1 == b2 && b1 == b3){
			//Collision inside triangle.
			return {true, intersect, ratio};
		}
		else{
			//No collision inside triangle.
			return {false};
		}

	}

	/// Collisionne un Segment (vecteur) et un modèle.
	/// \param vec Segment (vecteur).
	/// \param model Modèle.
	/// \return Structure de donnée contenant les résultats de la collision.
	static Physics::CollisionData collideVectorOnModel(Vector vec, Model& model){

		Physics::Triangle triangle;
		unsigned int pos = 0;
		Physics::CollisionData collisionResult;
		Vector normal;

		unsigned int triangleCount = model.vertexCount / 3;

		for(unsigned int i = 0; i < triangleCount; ++i) {

			pos = i * 9;

			//Extract triangle from model
			triangle = {
				//                  x                        y                       z
				{model.vertices[pos    ], model.vertices[pos + 1], model.vertices[pos + 2]}, // p1
				{model.vertices[pos + 3], model.vertices[pos + 4], model.vertices[pos + 5]}, // p2
				{model.vertices[pos + 6], model.vertices[pos + 7], model.vertices[pos + 8]}  // p3
			};

			//Average triangle normals
			normal = {
				((model.normals[pos    ] + model.normals[pos + 3] + model.normals[pos + 6]) / 3), // x
				((model.normals[pos + 1] + model.normals[pos + 4] + model.normals[pos + 7]) / 3), // y
				((model.normals[pos + 2] + model.normals[pos + 5] + model.normals[pos + 8]) / 3)  // z
			};

			collisionResult = collideVectorOnTri(vec, triangle, normal);

			if(collisionResult.collided){
				return collisionResult;
			}
		}

		return {false};
	}

	/// Collisionne la Hitbox d'un modèle et un segment de droite (vecteur).
	/// \param vec Segment.
	/// \param model Modèle.
	/// \return Structure de donnée contenant les résultats de la collision.
	static Physics::CollisionData collideVectorOnHitbox(Vector vec, Model& model){


		Physics::Triangle triangle;
		unsigned int pos = 0;
		Physics::CollisionData collisionResult;

		for(unsigned int i = 0; i < 12; ++i) {

			pos = i * 9;

			//Extract triangle from hitbox
			triangle = {
				{model.verticesHitBox[pos]    , model.verticesHitBox[pos + 1], model.verticesHitBox[pos + 2]},
				{model.verticesHitBox[pos + 3], model.verticesHitBox[pos + 4], model.verticesHitBox[pos + 5]},
				{model.verticesHitBox[pos + 6], model.verticesHitBox[pos + 7], model.verticesHitBox[pos + 8]}
			};

			collisionResult = collideVectorOnTri(vec, triangle, model.normalsHitBox[pos]);

			if(collisionResult.collided){
				return collisionResult;
			}
		}

		return {false};
	}

};

#endif //PHYSICS_H
