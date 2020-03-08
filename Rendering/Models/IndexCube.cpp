#include "IndexCube.hpp"

#define PI 3.14159265

void IndexCube::create(float x, float y, float z){
  GLuint vao;
  GLuint vbo;
  GLuint ibo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  std::vector<unsigned int> indices = { 
    0, 1, 2, 0, 2, 3, //front
    4, 5, 6, 4, 6, 7, //right
    8, 9, 10, 8, 10, 11, //back
    12, 13, 14, 12, 14, 15, //left
    16, 17, 18, 16, 18, 19, //upper
    20, 21, 22, 20, 22, 23}; //bottom

  std::vector<VertexFormat> vertices;
  //front
  vertices.push_back({{-0.5f+x, -0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 0.0f, 1.0f}});
  vertices.push_back({{ 0.5f+x, -0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 0.0f, 1.0f}});
  vertices.push_back({{ 0.5f+x, 0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 0.0f, 1.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 0.0f, 1.0f}});

  //right
  vertices.push_back({{0.5f+x, 0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {1.0f, 0.0f, 0.0f}});
  vertices.push_back({{0.5f+x, 0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {1.0f, 0.0f, 0.0f}});
  vertices.push_back({{0.5f+x, -0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {1.0f, 0.0f, 0.0f}});
  vertices.push_back({{0.5f+x, -0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {1.0f, 0.0f, 0.0f}});

  //back
  vertices.push_back({{-0.5f+x, -0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 0.0f, -1.0f}});
  vertices.push_back({{ 0.5f+x, -0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 0.0f, -1.0f}});
  vertices.push_back({{ 0.5f+x, 0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 0.0f, -1.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 0.0f, -1.0f}});

  //left
  vertices.push_back({{-0.5f+x, -0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {-1.0f, 0.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, -0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {-1.0f, 0.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {-1.0f, 0.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {-1.0f, 0.0f, 0.0f}});

  //upper
  vertices.push_back({{ 0.5f+x, 0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 1.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 1.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, 0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 1.0f, 0.0f}});
  vertices.push_back({{ 0.5f+x, 0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {0.0f, 1.0f, 0.0f}});

  //bottom
  vertices.push_back({{-0.5f+x, -0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {0.0f, -1.0f, 0.0f}});
  vertices.push_back({{ 0.5f+x, -0.5f+y, -0.5f+z},
      {1, 0, 0, 1},
      {0.0f, -1.0f, 0.0f}});
  vertices.push_back({{ 0.5f+x, -0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {0.0f, -1.0f, 0.0f}});
  vertices.push_back({{-0.5f+x, -0.5f+y, 0.5f+z},
      {1, 0, 0, 1},
      {0.0f, -1.0f, 0.0f}});


  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 
      sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
      sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
      (void*)(offsetof(VertexFormat, VertexFormat::color)));
  glBindVertexArray(0);
  this->vao = vao;
  this->vbos.push_back(vbo);
  this->vbos.push_back(ibo);

  rotation_speed = glm::vec3(90.0, 90.0, 90.0);
  rotation = glm::vec3(0.0, 0.0, 0.0);

}

void IndexCube::update(){

}

void IndexCube::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){
  rotation = 0.01f * rotation_speed + rotation;
  glm::vec3 rotation_sin = 
    glm::vec3(rotation.x*PI/180, rotation.y*PI/180, rotation.z*PI/180);

  glUseProgram(program);
  glUniform3f(glGetUniformLocation(program, "rotation"),
      rotation_sin.x,
      rotation_sin.y,
      rotation_sin.z);
  glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"),
      1, false, &view_matrix[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 
      1, false, &projection_matrix[0][0]);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}
