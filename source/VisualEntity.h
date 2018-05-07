#ifndef VISUALENTITY_H
#define VISUALENTITY_H

#include "includes.h"

class VisualEntity : public Entity, public Observer<SDL_Event*> {
public:
  std::function<void()> onClick;
  Vector position;
  bool visible;

  VisualEntity(const std::string& name, const Vector& position, bool visible = true) : Entity(name) {
      onClick = nullptr;
    this->position = position;
    this->visible = true;
  }

  virtual void draw() = 0;
};

#endif
