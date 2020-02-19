#version 430 core 
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 projection_matrix, view_matrix;
uniform vec3 rotation;

out vec4 color;

void main(){
  //color = vec4(in_color[0] + sin(rotation.x), in_color[1] + tan(rotation.y),
  //in_color[2] + sin(rotation.z), in_color[3]);
  color = in_color;
  mat4 rotate_x, rotate_y, rotate_z;

  rotate_x = mat4(1.0, 0.0, 0.0, 0.0,
      0.0, cos(rotation.x), sin(rotation.x), 0.0,
      0.0, -sin(rotation.x), cos(rotation.x), 0.0,
      0.0, 0.0, 0.0, 1.0);

  rotate_y = mat4(cos(rotation.y), 0.0, -sin(rotation.y), 0.0,
      0.0, 1.0, 0.0, 0.0,
      sin(rotation.y), 0.0, cos(rotation.y), 0.0,
      0.0, 0.0, 0.0, 1.0);

  rotate_z = mat4(cos(rotation.z), -sin(rotation.z), 0.0, 0.0,
      sin(rotation.z), cos(rotation.z), 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0);

  gl_Position = projection_matrix * view_matrix * 
    vec4(in_position, 1);
  //gl_Position = projection_matrix * view_matrix * 
  //  rotate_y * rotate_x * rotate_z * vec4(in_position, 1);
  /*mat4 translate = mat4(
      1,0,0,-in_position.x,
      0,1,0,-in_position.y,
      0,0,1,-in_position.z,
      0,0,0,1
      );
  mat4 translate2 = mat4(
      1,0,0,in_position.x,
      0,1,0,in_position.y,
      0,0,1,in_position.z,
      0,0,0,1
      );
  gl_Position = projection_matrix * view_matrix * 
    translate2 * rotate_y * rotate_x * rotate_z * translate * vec4(in_position, 1);
  */
}
