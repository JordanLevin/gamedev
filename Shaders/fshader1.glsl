#version 430 core
layout(location = 0) out vec4 out_color;

in vec4 color;
//in vec3 normal;
in vec4 light_color;
in float light_power;
 
void main()
{
  out_color = color;
}
