#ifndef LOGGER_H
#define LOGGER_H

/**
  * Logger will log messages from different sources at different levels
  * Stats will be tracked ~somehow~
  * eventually logger will be trackable in a gui
  */
class Logger {
  std::mutex lock;
  int level;

  std::unordered_map<std::string, int> stats;

  public:
    void INFO(){

    }
    void ERROR(){

    }
    void FATAL(){

    }
    
};


#endif
