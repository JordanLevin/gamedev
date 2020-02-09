#ifndef LISTENER_H
#define LISTENER_H

class IListener{
  public:
    virtual ~IListener() = 0;

    virtual void notifyBeginFrame() = 0;
    virtual void notifyDisplayFrame() = 0;
    virtual void notifyEndFrame() = 0;
    virtual void notifyReshape(int width, int height, 
                               int pwidth, int pheight) = 0;
};

inline IListener::~IListener(){

}

#endif
