/// \brief Classe de méthodes statiques pour les calculs de physique et de collisions.
/// \details
/// \author Samuel Labelle
/// \date  mai 2018
/// \version 0.2
/// \warning Non extensivement testée, les métodes de collision sont suceptibles de collisionner sur n'importe quel triangle d'un modèle se trouvant dans une trajectoire de collision.
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

	/// Collisionne un segment et un plan infini.
	/// \param segmentOrigin Point de départ du segment.
	/// \param segment Segment (Vecteur)
	/// \param normalOrigin Point faisant partie de la surface plane.
	/// \param planeNormal Normale de la surface plane infinie.
	/// \return Structure de données contenant les résultats de la collision.
	static PhysicsData::CollisionData collideVectorOnPlane(Vector segmentOrigin, Vector segment, Vector normalOrigin, Vector planeNormal){
		planeNormal.normalize();

		double dotp = planeNormal * segment;

		if((PHYSICS_EPSILON > dotp) && (dotp > -PHYSICS_EPSILON))
			return {false};

		double ratio = ((planeNormal * normalOrigin) / (planeNormal * segment));

		if(ratio > 1 || ratio < 0)
			return {false};


		return {true, segmentOrigin + (segment * ratio)/*intersect*/, ratio};
	}

	/// Détermine si un point se trouve à l'intérieur d'un triangle.
	/// \param point Le point.
	/// \param tri Le triangle.
	/// \param normal Vecteur normalisé représentant la normale du triangle.
	/// \return Le point se trouve dans le triangle. (booléen)
	static bool isPointWithinTri(Vector point, PhysicsData::Triangle tri, Vector normal){
		PhysicsData::FlatTriangle flatTri;
		PhysicsData::Vec2D flatVec;

		if((normal.x > normal.y) && (normal.x > normal.z)){
			//remove x from tri
			flatTri = {{tri.p1.y, tri.p1.z}, {tri.p2.y, tri.p2.z}, {tri.p3.y, tri.p3.z}};
			flatVec = {point.y, point.z};
		}
		else if(normal.y > normal.z){
			//remove y from tri
			flatTri = {{tri.p1.x, tri.p1.z}, {tri.p2.x, tri.p2.z}, {tri.p3.x, tri.p3.z}};
			flatVec = {point.x, point.z};
		}
		else{
			//remove z from tri
			flatTri = {{tri.p1.x, tri.p1.y}, {tri.p2.x, tri.p2.y}, {tri.p3.x, tri.p3.y}};
			flatVec = {point.x, point.y};
		}

		bool b1 = signbit(det22(flatVec.x, flatVec.y, flatTri.p1.x, flatTri.p1.y));
		bool b2 = signbit(det22(flatVec.x, flatVec.y, flatTri.p2.x, flatTri.p2.y));
		bool b3 = signbit(det22(flatVec.x, flatVec.y, flatTri.p3.x, flatTri.p3.y));

		if(b1 == b2 && b1 == b3){
			//Collision inside triangle.
			return true;
		}
		else{
			//No collision inside triangle.
			return false;
		}
	}

	/// Collisionne un segment et un triangle.
	/// \param segmentOrigin Point de départ du segment.
	/// \param segment Segment (Vecteur)
	/// \param tri Triangle.
	/// \param normal Normale du triangle.
	/// \return Structure de données contenant les résultats de la collision.
	static PhysicsData::CollisionData collideVectorOnTri(Vector segmentOrigin, Vector segment, PhysicsData::Triangle tri, Vector normal){

		PhysicsData::CollisionData cData = collideVectorOnPlane(segmentOrigin, segment, tri.p1, normal);
		bool pointInTriangle = isPointWithinTri(cData.point, tri, normal);

		if(pointInTriangle){
			//Collision inside triangle.
			return {true, cData.point, cData.ratio};
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
	/// \return Structure de données contenant les résultats de la collision.
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
	/// \return Structure de données contenant les résultats de la collision.
	static PhysicsData::CollisionData collideVectorOnHitbox(Vector origin, Vector vec, Model& model){

		PhysicsData::Triangle triangle;
		unsigned int pos = 0;
		PhysicsData::CollisionData collisionResult;
		Vector normal;

		for(unsigned int i = 0; i < 12; ++i) {

			pos = i * 9;

			//Extract triangle from hitbox
			triangle = {
				{model.verticesHitBox[pos]    , model.verticesHitBox[pos + 1], model.verticesHitBox[pos + 2]},
				{model.verticesHitBox[pos + 3], model.verticesHitBox[pos + 4], model.verticesHitBox[pos + 5]},
				{model.verticesHitBox[pos + 6], model.verticesHitBox[pos + 7], model.verticesHitBox[pos + 8]}
			};

			//Average triangle normals
			normal = {
				((model.normalsHitBox[pos    ] + model.normalsHitBox[pos + 3] + model.normalsHitBox[pos + 6]) / 3), // x
				((model.normalsHitBox[pos + 1] + model.normalsHitBox[pos + 4] + model.normalsHitBox[pos + 7]) / 3), // y
				((model.normalsHitBox[pos + 2] + model.normalsHitBox[pos + 5] + model.normalsHitBox[pos + 8]) / 3)  // z
			};

			collisionResult = collideVectorOnTri(origin, vec, triangle, normal);

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
	/// \return Structure de données contenant les résultats de la collision.
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
	/// \return Structure de données contenant les résultats de la collision.
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

	/// Trouve le point faisant partie d'un segment de droite qui est le plus rapproché d'un autre point situé ailleurs dans l'espace.
	/// \param searchOrigin Point dont on recherche le point le plus rapproché sur lw segment de droite.
	/// \param a Point un délimitant le segment de droite.
	/// \param b Point deux délimitant le segment de droite.
	/// \return Point le plus rapproché du point de recherche se trouvant sur le segment de droite.
	static Vector getClosestPointOnLineSegment(Vector searchOrigin, Vector a, Vector b) {

		// Determine length of A-->Point vector.
		Vector c = searchOrigin - a;

		// Get a normalised vector that is co-linear with AB for projection.
		Vector V = (b - a).normalize();

		double j = (b.x - a.x), k = (b.y - a.y), l = (b.z - a.z);
		double d = j*j + k*k + l*l; // Do not square root this.

		double projectionLength = V * c;

		// See if projected point is not on the segment and, if so, return the appropriate end of the segment.

		if (projectionLength < 0) return a;

		if ((projectionLength * projectionLength) > d) return b; // Avoid computing the square root of d by squaring t, less processor intensive.

		// Return projected point on segment

		V.normalize();
		V = V * projectionLength;

		return a + V;

	}

	/// Trouve le point des côtés d'un triangle le plus rapproché d'un autre point ailleurs dans l'espace.
	/// \param point Point dont on cherche le point le plus rapproché.
	/// \param tri Triangle.
	/// \return Point faisant partie des côtés du triangle le plus proche du point de recherche.
	static Vector getClosestPointOnTriSides(Vector point, PhysicsData::Triangle tri) {

		Vector p12 = getClosestPointOnLineSegment(tri.p1, tri.p2, point);
		Vector p23 = getClosestPointOnLineSegment(tri.p2, tri.p3, point);
		Vector p31 = getClosestPointOnLineSegment(tri.p3, tri.p1, point);

		double np12 = p12.getSquaredNorm(), np23 = p23.getSquaredNorm(), np31 = p31.getSquaredNorm();

		if (np12 >= np23)
		{
			if (np12 >= np31)
				return p12;
			else
				return p31;
		}
		else
		{
			if (np23 >= np31)
				return p23;
			else
				return p31;
		}

	}

	/// Collisionne un vecteur sur une sphère.
	/// \param vectorOrigin Point d'origine du vecteur.
	/// \param vector Vecteur.
	/// \param sphereOrigin Point d'origine de la sphère.
	/// \param sphereRadius Rayon de la sphère.
	/// \return Structure de données contenant les résultats de la collision.
	static PhysicsData::CollisionData collideVectorOnSphere(Vector vectorOrigin, Vector vector, Vector sphereOrigin, double sphereRadius){
		Vector normalizedVector(vector.getNormalized());

		Vector Q = sphereOrigin - vectorOrigin; // Vector from vectorOrigin to sphereOrigin

		double c = Q.x * Q.x + Q.y * Q.y + Q.z * Q.z; //distance squared between vectorOrigin and sphereOrigin;

		double v = Q * normalizedVector; // Project Q on vector to collide

		double d = sphereRadius*sphereRadius - (c - v*v);

		// Failure to intersect, return false.
		if (d < 0.0) {
			return {false};
		}


		double distanceToIntersect = (v - sqrt(d));

		return {true, vectorOrigin + (normalizedVector * distanceToIntersect), distanceToIntersect / vector.getNorm()};
	}

	/// Collisionne une sphère en mouvement sur un triangle.
	/// \param sphereMovement Déplacement de la sphère.
	/// \param sphereCenter Point centre de la sphère.
	/// \param sphereRadius Rayon de la sphère.
	/// \param tri Triangle.
	/// \param triangleNormal Vecteur normal du triangle.
	/// \return Structure de données contenant les résultats de la collision.
	static PhysicsData::CollisionData collideMovingSphereOnTri(Vector& sphereMovement, Vector& sphereCenter, double& sphereRadius, PhysicsData::Triangle& tri, Vector& triangleNormal ){

		triangleNormal.normalize();
		// make a triangle with sphere radius added in the normal direction. (so we get the sphere center point when colliding.)
		Vector collisionPoint(sphereCenter + (-triangleNormal * sphereRadius));

		PhysicsData::CollisionData cData = collideVectorOnPlane(collisionPoint, sphereMovement, tri.p1, triangleNormal);

		if(isPointWithinTri(cData.point, tri, triangleNormal)) {
			return cData;
		}
		// Sphere center failing collision with the main triangle body, check collision with triangle sides (and verticies).
		// get point on triangle sides closest to sphere center point.
		Vector nearestPointToTriOnPlaneCollision = getClosestPointOnTriSides(cData.point, tri);

		PhysicsData::CollisionData cData2 = collideVectorOnSphere(nearestPointToTriOnPlaneCollision, -sphereMovement, sphereCenter, sphereRadius);

		if(cData2.collided)
			return {true, -cData2.point, cData2.ratio};
		else
			return {false};


	}

	/// Collisionne une sphère en mouvement sur un modèle.
	/// \param sphereMovement Vecteur de déplacement de la sphère.
	/// \param sphereCenter Centre de la sphère.
	/// \param sphereRadius Rayon de la sphère.
	/// \param model Modèle su lequel collisionner la sphère.
	/// \return Structure de données contenant les résultats de la collision.
	static PhysicsData::CollisionData collideMovingSphereOnModel(Vector& sphereMovement, Vector& sphereCenter, double& sphereRadius, Model& model){

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

			collisionResult = collideMovingSphereOnTri(sphereMovement, sphereCenter, sphereRadius, triangle, normal);

			if(collisionResult.collided){
				return collisionResult;
			}
		}

		return {false};
	}

	/// Collisionne une sphère en mouvement sur une sphère immobile
	/// \param sphereMovement Vecteur de déplacement de la sphère en mouvemnent.
	/// \param movingSphereCentre
	/// \param movingSphereRadius Rayon de la sphère en mouvement.
	/// \param staticSphereCenter
	/// \param staticSphereRadius Rayon de la sphère immobile.
	/// \return Structure de données contenant les résultats de la collision, le point est le point de collision sur surface de la sphère statique et le ratio correspond au rapport entre la norme du vecteur déplacement et la distance parcourue avant la collision.
	static PhysicsData::CollisionData collideMovingSphereOnSphere(Vector sphereMovement,
	                                                              Vector movingSphereCentre, double movingSphereRadius,
	                                                              Vector staticSphereCenter, double staticSphereRadius){
		// add early collision detection avoidance using radii sum test ?

		// Transforming the moving sphere in a point and transfer its radius to the other sphere.
		PhysicsData::CollisionData cData = collideVectorOnSphere(movingSphereCentre, sphereMovement, staticSphereCenter, movingSphereRadius + staticSphereRadius);

		return {cData.collided, (staticSphereCenter - cData.point).normalize() * movingSphereRadius, cData.ratio};
		// this should do the trick : (staticSphereCenter - cData.point).normalize() * movingSphereRadius;
		// the ratio is between the movement vector and the new moving sphere center

	}

	static PhysicsData::CollisionData collideMovingSpheres(Vector sphere1Movement, Vector sphere1Center, double sphere1Radius,
														   Vector sphere2Movement, Vector sphere2Center, double sphere2Radius) {
	}

	/*
	satic PhysicsData::CollisionData collideMovingSphereOnPoint(){

	}

	static PhysicsData::CollisionData collideMovingSphereOnModel(){

	}
*/
};

#endif //PHYSICS_H
