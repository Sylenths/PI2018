/// \brief Représentation d'une image.
/// \details Crée un modèle 3D plat pour y recevoir une texture.
/// \author Gabriel Bourdages, Samuel Labelle, Patrick Singcaster
/// \date 28 mars 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef IMAGE_H
#define IMAGE_H

class Image : public Model {
public:
    /// Constructeur.
    /// \param textureID Identificateur de la texture.
    /// \param x Position en x par rapport au coin supérieur gauche.
    /// \param y Position en y par rapport au coin supérieur gauche.
    /// \param width Largeur de l'image.
    /// \param height Hauteur de l'image.
    Image(double x, double y, double z, double width, double height, unsigned int textureID) : Model(x, y, z, textureID) {
      texCount = 12;
      vertexCount = normalCount = 18;

      vertices = new double[18] { x, y, z, width + x, height + y, z, x, height + y, z, x, y, z, width + x, y, z, width + x, height + y, z };
      normals = new double[18] { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 };
      texCoords = new double[12] { 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0,1.0 };
    }

  /// Réception de notifications d'événements SDL.
  /// \param sdlEvent Événement SDL.
  virtual void notify(SDL_Event* sdlEvent) {}
};

#endif
