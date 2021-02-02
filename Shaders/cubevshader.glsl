#version 430 core 
layout(location = 0) in uint vdata;
//#layout(location = 0) in vec3 in_position;
//#layout(location = 1) in vec4 in_color;
//#layout(location = 2) in vec3 in_normal;

uniform mat4 projection_matrix, view_matrix, model_matrix;
uniform vec4 light_color_in;
uniform float light_power_in;
uniform vec3 light_dir;
uniform int wireframe;

out vec4 color;
out vec3 normal;
out vec4 light_color;
out float light_power;
out uint temp;

vec4 getColor(uint type){
  if(type == 1)
    return vec4(0.066f, 0.396f, 0.043f, 1.0f);
  if(type == 2)
    return vec4(1.0f,1.0f,1.0f,1.0f);
  if(type == 3)
    return vec4(0.5f,0.5f,0.5f,1.0f);
  if(type == 4)
    return vec4(0.3f,1.0f,1.0f,0.8f);
  if(type == 6)
    return vec4(0.909, 0.843, 0.172, 1.0f); // yellow
  if(type == 7)
    return vec4(0.094, 0.141, 0.725, 1.0f); // blue
  return vec4(0.294, 0.141, 0.725, 1.0f); // idk
}

//#VERTEX FORMAT: 
//# n n n c c c c z z z z z y y y y y y y x x x x x

vec3 extractPos(uint vert){
  float x = float(vert & 31u);
  float y = float((vert >> 5) & 127u);
  float z = float((vert >> 12) & 31u);
  return vec3(x,y,z);
}

vec4 extractCol(uint vert){
  uint col = (vert >> 17) & 15u;
  return getColor(col);
}

vec3 extractNorm(uint vert){
  uint norm = (vert >> 21) & 7u;
  return vec3( float(norm & 1u) , float(norm >> 1 & 1u), float(norm >> 2 & 1u)); 
}

void main(){
  temp = vdata;
  vec3 in_position = extractPos(vdata);
  vec4 in_color = extractCol(vdata);
  vec3 normal = extractNorm(vdata);

  if(wireframe == 1)
    color = vec4(0,0,0,1);
  light_color = light_color_in;
  light_power = light_power_in;

  vec3 AmbientColor = vec3(0.2,0.2,0.2) * in_color.xyz;
  color = vec4(
      //Ambient lighting
      AmbientColor + 
      in_color.xyz * light_color.xyz * (abs(normal.x) * 0.7 + abs(normal.y) * 0.8 + abs(normal.z) * 0.6), 1);

  gl_Position = projection_matrix * view_matrix * model_matrix * 
    vec4(in_position, 1);
}
