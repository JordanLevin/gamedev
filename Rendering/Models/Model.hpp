#ifndef MODEL_H
#define MODEL_H

#include "../IGameObject.hpp"

#include <GL/glew.h>

#include <vector>

class Model: public IGameObject{
  protected:
    GLuint vao;
    GLuint program;
    std::vector<GLuint> vbos;

  public:
    Model() = default;
    virtual ~Model();
    virtual void draw() override;
    virtual void draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
    virtual void update() override;
    virtual void setProgram(GLuint shaderName) override;
    virtual void destroy() override;

    virtual GLuint getVao() const override;
    virtual const std::vector<GLuint>& getVbos() const override;

};

#endif
