#ifndef INCLUDES_H
#define INCLUDES_H

#define IS2D true
#define IS3D false

#define BUILD_NOTHING 0
#define BUILD_FONDATION 1
#define BUILD_WALL 2
#define BUILD_FLOOR 3
#define BUILD_ROOF 4
#define BUILD_WIRE 5
#define DELETE 6

#define NULLMATERIAL 0
#define CARDBOARD 1
#define WOOD 2
#define ROCK 3
#define METAL 4
#define SIMTIUM 5
#define COPPER 1
#define SILVER 2
#define GOLD 3
#define DDP 120

#include <list>
#include <cmath>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <stack>
#include <utility>
#include <functional>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#if defined(_WIN32) || defined(__linux__)
  #include <SDL2/SDL_ttf.h>
  #include <SDL2/SDL_image.h>
#elif defined __APPLE__
  #include <SDL2_ttf/SDL_ttf.h>
  #include <SDL2_image/SDL_image.h>
#endif

#include "Entity.h"
#include "EntityManager.h"
#include "Texture2d.h"
#include "Chrono.h"
#include "Singleton.h"
#include "Observable.h"
#include "Vector2d.h"
#include "Vector.h"
#include "Matrix.h"
#include "GLContext.h"
#include "Model.h"
#include "Meteorite.h"

#include "Materiel.h"
#include "Structure.h"
#include "Floor.h"
#include "Fondation.h"
#include "Font.h"
#include "Camera.h"
#include "Scene.h"
#include "VisualEntity.h"
#include "VisualEntity2d.h"
#include "Image.h"
#include "Image2d.h"
#include "Label.h"
#include "Label2d.h"
#include "Button.h"
#include "Button2d.h"
#include "CheckBox.h"
#include "Menu.h"
#include "Menu2d.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "ResolutionMenu.h"
#include "InGameOverlay.h"
#include "PauseMenu.h"
#include "Scores.h"
#include "HighScoresMenu.h"
#include "Light.h"
#include "World.h"
#include "ProjetFinal.h"
#include "Action.h"
#include "PowerManager.h"
#include "Wall.h"
#include "Roof.h"

#endif
