#ifndef LIGHT_H
#define LIGHT_H

class Light {
private:
  float position[4];

public:
  Light(const float& x, const float& y, const float& z, const float& w) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
    position[3] = w;
  }

  void applyLightPosition() {
    glLightfv(GL_LIGHT0, GL_POSITION, position);
  }
};

#endif
