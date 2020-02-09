#ifndef WINDOWINFO_H
#define WINDOWINFO_H

#include <string>

struct WindowInfo{
  std::string name;
  int posx;
  int posy;
  int width;
  int height;
  bool reshapable;

  WindowInfo(){
    name = "GAME Engine";
    width = 800;
    height = 600;
    posx = 300;
    posy = 300;
    reshapable = true;
  }

  WindowInfo(std::string n, int posxi, int posyi, int w, int h, bool reshape)
    :name{n}, posx{posxi}, posy{posyi}, width{w}, height{h}, reshapable{reshape}
  {}

  WindowInfo(const WindowInfo& windowInfo) = default;
  WindowInfo& operator=(const WindowInfo& windowInfo) = default;
};

#endif
