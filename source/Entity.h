#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
private:
  std::string name;

public:
  Entity(const std::string& name) { this->name = name; }

  const std::string& getName() { return name; }
};

#endif
