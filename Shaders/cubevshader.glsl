#version 430 core 
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;

uniform mat4 projection_matrix, view_matrix;
uniform vec4 light_color_in;
uniform float light_power_in;
uniform vec3 light_dir;

out vec4 color;
out vec3 normal;
out vec4 light_color;
out float light_power;

void main(){
  color = in_color;
  normal = in_normal;
  light_color = light_color_in;
  light_power = light_power_in;

  float cosTheta = clamp(dot(normal, light_dir), 0, 1);

  vec3 AmbientColor = vec3(0.2,0.2,0.2) * color.xyz;
  color = vec4(
      //Ambient lighting
      AmbientColor + 
      //Diffuse lighting
      color.xyz * light_color.xyz * light_power * cosTheta, 1);

  gl_Position = projection_matrix * view_matrix * 
    vec4(in_position, 1);
}
