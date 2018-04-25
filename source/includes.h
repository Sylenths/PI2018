#ifndef INCLUDES_H
#define INCLUDES_H

#define IS2D true
#define IS3D false

#include <list>
#include <cmath>
#include <string>
#include <functional>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#if defined(_WIN32) || defined(__linux__)
  #include <SDL2/SDL_ttf.h>
  #include <SDL2/SDL_image.h>
#elif defined __APPLE__
  #include <SDL2_ttf/SDL_ttf.h>
  #include <SDL2_image/SDL_image.h>
#endif


#include <iostream>
#include <utility>
#include <functional>
#include "Chrono.h"
#include "Singleton.h"
#include "Observable.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Vector.h"
#include "Matrix.h"
#include "GLContext.h"
#include "Model.h"
#include "Materiel.h"
#include "Structure.h"
#include "Fondation.h"
#include "Font.h"
#include "Image.h"
#include "Scene.h"
#include "Menu.h"
#include "Button.h"
#include "Label.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "InGameOverlay.h"
#include "PauseMenu.h"
#include "Scores.h"
#include "HighScoresMenu.h"
#include "Light.h"
#include "World.h"
#include "ProjetFinal.h"
#include "Camera.h"
#include "Action.h"
#include "PowerManager.h"

#endif
