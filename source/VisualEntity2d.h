#ifndef VISUALENTITY2D_H
#define VISUALENTITY2D_H

#include "includes.h"

class VisualEntity2d : public VisualEntity {
protected:
    Vector2d size;

public:
  VisualEntity2d(const std::string& name, const Vector& position, const Vector2d& size, bool visible = true) : VisualEntity(name, position, visible) {
      this->size = size;
  }

  virtual void draw() = 0;
};

#endif
