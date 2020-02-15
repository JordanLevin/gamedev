#ifndef MODEL_H
#define MODEL_H

#include "../IGameObject.hpp"

#include <GL/glew.h>

#include <vector>

class Model: public IGameObject{
  public:
    Model() = default;
    virtual ~Model();
    virtual void draw() override;
    virtual void update() override;
    virtual void setProgram(GLuint shaderName) override;
    virtual void destroy() override;

    virtual GLuint getVao() const override;
    virtual const std::vector<GLuint>& getVbos() const override;

  protected:
    GLuint vao;
    GLuint program;
    std::vector<GLuint> vbos;
};

#endif