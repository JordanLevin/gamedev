#ifndef LOGGER_H
#define LOGGER_H

#include <thread>
#include <string>
#include <mutex>
#include <ctime>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <ostream>
#include <iostream>

#define SET_LOG_CATEGORY(x) static const std::string __logger_category = x
#define __LOG_LEVEL 4

#if __LOG_LEVEL >= 5
#define LOG_DEBUG \
  __LOGGER.logMetaData(__logger_category, "DEBUG"); \
  __LOGGER
#else
#define LOG_DEBUG doot
#endif

//#define LOG_INFO(x)  \
  //if constexpr(__LOGGER.d_level >= 4) Logger::INFO(x, __logger_category)
//#define LOG_ERROR(x)  \
  //if constexpr(__LOGGER.d_level >= 3) Logger::ERROR(x, __logger_category)
//#define LOG_WARNING(x) \
  //if constexpr(__LOGGER.d_level >= 2) Logger::WARNING(x, __logger_category)
//#define LOG_FATAL(x)  \
  //if constexpr(__LOGGER.d_level >= 1) Logger::FATAL(x, __logger_category)

/**
 * Logger will log messages from different sources at different levels
 * Stats will be tracked ~somehow~
 * eventually logger will be trackable in a gui
 */
class Logger {
  private:
    std::mutex d_lock;

    std::unordered_map<std::string, int> d_stats;
    std::ostream& d_stream = std::cout;


  public:
    int d_log_level = 4;

    void logMetaData(std::string category, std::string level){
      d_lock.lock();
      std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      d_stream << 
        std::ctime(&now) << " " << 
        std::this_thread::get_id() << " " <<  
        level << " " << 
        category << ": ";
      d_lock.unlock();
    }

    operator std::ostream(){
      return d_stream;
    }

    template<class T>
    Logger& operator<<(const T& data){
      d_lock.lock();
      d_stream << data;
      d_lock.unlock();
      return *this;
    }

};

Logger __LOGGER;


#endif
