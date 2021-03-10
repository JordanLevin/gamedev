#ifndef CUBE_H
#define CUBE_H

#include <cstdint>

struct Cube {
  uint8_t x, y, z;
  uint8_t type;
};

struct WorldCube {
  int x, y, z;
  uint8_t type;
};

#endif
