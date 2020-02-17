#include "Model.hpp"

Model::~Model(){
  destroy();
}
void Model::draw(){

}
void Model::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix){

}
void Model::update(){

}
void Model::setProgram(GLuint program_){
  program = program_;
}
GLuint Model::getVao() const {
  return vao;
}
const std::vector<GLuint>& Model::getVbos() const { 
  return vbos;
}
void Model::destroy(){
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(vbos.size(), &vbos[0]);
  vbos.clear();
}
