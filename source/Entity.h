#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Resource.h"

class Entity : public Resource {
private:
  std::string name;

public:
  Entity(const std::string& name) { this->name = name; }

  const std::string& getName() { return name; }
  const std::string getType() { return "Entity"; }
};

#endif
