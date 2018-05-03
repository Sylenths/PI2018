/// \brief Classe de méthodes statiques pour les calculs de physique et de collisions.
/// \details
/// \author Samuel Labelle
/// \date 25 Avril 2018
/// \version 0.2
/// \warning Non extensivement testée
/// \bug Les calculs ne sont pas optimisés.

#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector.h"
#include "Matrix.h"
#include "Model.h"
#include "MathUtils.h"

#define PHYSICS_EPSILON 0.000001

namespace PhysicsData {

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
	/// \param segmentOrigin Point de départ du segment.
	/// \param segment Segment (Vecteur)
	/// \param tri Triangle.
	/// \param normal Normale du triangle.
	/// \return Structure de donnée contenant les résultats de la collision.
	static PhysicsData::CollisionData collideVectorOnTri(Vector segmentOrigin, Vector segment, PhysicsData::Triangle tri, Vector normal){
		normal.normalize();

		double dotp = normal * segment;

		if((PHYSICS_EPSILON > dotp) && (dotp > -PHYSICS_EPSILON))
			return {false};

		double ratio = ((normal * tri.p1) / (normal * segment));

		if(ratio > 1)
			return {false};

		Vector intersect(segmentOrigin + (segment * ratio));

		PhysicsData::FlatTriangle flatTri;
		PhysicsData::Vec2D flatVec;

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
	/// \param origin Point de départ du segment.
	/// \param vec Segment (vecteur).
	/// \param model Modèle.
	/// \return Structure de donnée contenant les résultats de la collision.
	static PhysicsData::CollisionData collideVectorOnModel(Vector origin, Vector vec, Model& model){

		PhysicsData::Triangle triangle;
		unsigned int pos = 0;
		PhysicsData::CollisionData collisionResult;
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

			collisionResult = collideVectorOnTri(origin, vec, triangle, normal);

			if(collisionResult.collided){
				return collisionResult;
			}
		}

		return {false};
	}

	/// Collisionne la Hitbox d'un modèle et un segment de droite (vecteur).
	/// \param origin Point de départ du segment.
	/// \param vec Segment.
	/// \param model Modèle.
	/// \return Structure de donnée contenant les résultats de la collision.
	static PhysicsData::CollisionData collideVectorOnHitbox(Vector origin, Vector vec, Model& model){

		PhysicsData::Triangle triangle;
		unsigned int pos = 0;
		PhysicsData::CollisionData collisionResult;

		for(unsigned int i = 0; i < 12; ++i) {

			pos = i * 9;

			//Extract triangle from hitbox
			triangle = {
				{model.verticesHitBox[pos]    , model.verticesHitBox[pos + 1], model.verticesHitBox[pos + 2]},
				{model.verticesHitBox[pos + 3], model.verticesHitBox[pos + 4], model.verticesHitBox[pos + 5]},
				{model.verticesHitBox[pos + 6], model.verticesHitBox[pos + 7], model.verticesHitBox[pos + 8]}
			};

			collisionResult = collideVectorOnTri(origin, vec, triangle, model.normalsHitBox[pos]);

			if(collisionResult.collided){
				return collisionResult;
			}
		}

		return {false};
	}

	/// Collisionne la hitbox d'un modèle en mouvement sur la hitbox d'un modèle fixe.
	/// \param model1Movement Déplacement du modèle en mouvement.
	/// \param model1 Modèle en mouvement
	/// \param model2 Modèle fixe.
	/// \return Structure de donnée contenant les résultats de la collision.
	static PhysicsData::CollisionData collideMovingOnStaticModelHitboxes(Vector model1Movement, Model& model1, Model& model2){

		PhysicsData::CollisionData collisionResult;

		unsigned int x;

		//For each point in model1, collide with model2
		for(unsigned int i = 0; i < 36/*vertexcount*/; ++i) {
			x = i * 3;

			collisionResult = collideVectorOnHitbox(
				{model1.verticesHitBox[x],
				 model1.verticesHitBox[x + 1],
				 model1.verticesHitBox[x + 2]
				},
				model1Movement,
				model2);

			if(collisionResult.collided)
				return collisionResult;
		}

		model1Movement = -model1Movement;

		for(unsigned int i = 0; i < 36/*vertexcount*/; ++i) {
			x = i * 3;

			collisionResult = collideVectorOnHitbox(
				{model2.verticesHitBox[x],
				 model2.verticesHitBox[x + 1],
				 model2.verticesHitBox[x + 2]
				},
				model1Movement,
				model1);

			if(collisionResult.collided)
				return collisionResult;
		}

		return {false};
	}

	/// Collisionne un modèle en mouvement sur un modèle fixe.
	/// \param model1Movement Déplacement du modèle en mouvement.
	/// \param model1 Modèle en mouvement
	/// \param model2 Modèle fixe.
	/// \return Structure de donnée contenant les résultats de la collision.
	static PhysicsData::CollisionData collideMovingOnStaticModels(Vector model1Movement, Model& model1, Model& model2){

		PhysicsData::CollisionData collisionResult;

		unsigned int x;

		//For each point in model1, collide with model2
		for(unsigned int i = 0; i < model1.vertexCount; ++i) {
			x = i * 3;

			collisionResult = collideVectorOnHitbox(
				{model1.vertices[x],
				 model1.vertices[x + 1],
				 model1.vertices[x + 2]
				},
				model1Movement,
				model2);

			if(collisionResult.collided)
				return collisionResult;
		}

		model1Movement = -model1Movement;

		for(unsigned int i = 0; i < model2.vertexCount; ++i) {
			x = i * 3;

			collisionResult = collideVectorOnHitbox(
				{model2.vertices[x],
				 model2.vertices[x + 1],
				 model2.vertices[x + 2]
				},
				model1Movement,
				model1);

			if(collisionResult.collided)
				return collisionResult;
		}

		return {false};
	}

};

#endif //PHYSICS_H
