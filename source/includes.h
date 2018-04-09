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

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#if defined(_WIN32) || defined(__linux__)
  #include <SDL2/SDL_ttf.h>
  #include <SDL2/SDL_image.h>
#elif defined __APPLE__
  #include <SDL2_ttf/SDL_ttf.h>
  #include <SDL2_image/SDL_image.h>
#endif

#include "Chrono.h"
#include "Singleton.h"
#include "Observable.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Vector.h"
#include "Matrix.h"
#include "GLContext.h"
#include "Model.h"
#include "Font.h"
#include "Image.h"
#include "Scene.h"
#include "Menu.h"
#include "Button.h"
#include "Label.h"
#include "MainMenu.h"
#include "Settings.h"
#include "InGameOverlay.h"
#include "InGameESC.h"
#include "Highscore.h"
#include "World.h"
#include "ProjetFinal.h"


#endif
