#ifndef MESHER_H
#define MESHER_H

#include "Cube.hpp"
#include "VertexFormat.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <unordered_set>

class Mesher {
  private:
    //Functions for cube are here because cube must be an aggregate
    static glm::vec4 getColor(const Cube& c);

    static inline int getIndex(int x, int y, int z);

  public:
    Mesher() = default;
    ~Mesher() = default;

    static std::vector<uint32_t> createMesh(const std::vector<Cube>& chunk,
        const std::unordered_set<int>& occupied);
    static uint32_t compressVertex(VertexFormat in, uint8_t type);

};


#endif
