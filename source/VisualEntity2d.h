#ifndef VISUALENTITY2D_H
#define VISUALENTITY2D_H

#include "includes.h"

class VisualEntity2d : public VisualEntity {
public:
  VisualEntity2d(const std::string& name, const Vector& position, bool visible = true) : VisualEntity(name, position, visible) { }

  virtual void draw() = 0;
};

#endif
