#ifndef GAMEMODELS_H
#define GAMEMODELS_H

#include <GL/glew.h> 
#include <GL/freeglut.h> 
#include "../Rendering/VertexFormat.hpp"
#include <vector>
#include <map>
#include <string>

struct Model{
  unsigned int vao;
  std::vector<unsigned int> vbos;

  Model() = default;
};

class GameModels{
  public:
    GameModels();
    ~GameModels();
    void createTriangleModel(const std::string& gameModelName);
    void deleteModel(const std::string& gameModelName);
    unsigned int getModel(const std::string& gameModelName);
  private:
    std::map<std::string, Model> gameModelList;
};

#endif
