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

#define LOG_DEBUG(x)  \
  if constexpr(Logger::d_level >= 5) Logger::DEBUG(x, __logger_category)
#define LOG_INFO(x)  \
  if constexpr(Logger::d_level >= 4) Logger::INFO(x, __logger_category)
#define LOG_ERROR(x)  \
  if constexpr(Logger::d_level >= 3) Logger::ERROR(x, __logger_category)
#define LOG_WARNING(x) \
  if constexpr(Logger::d_level >= 2) Logger::WARNING(x, __logger_category)
#define LOG_FATAL(x)  \
  if constexpr(Logger::d_level >= 1) Logger::FATAL(x, __logger_category)

/**
 * Logger will log messages from different sources at different levels
 * Stats will be tracked ~somehow~
 * eventually logger will be trackable in a gui
 */
class Logger {
  private:
    static std::mutex d_lock;

    static std::unordered_map<std::string, int> d_stats;
    static constexpr std::ostream& d_stream = std::cout;

    static void log(std::string msg, std::string category){
      d_lock.lock();
      std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      d_stream << std::ctime(&now) << " " << std::this_thread::get_id() << " " <<  category << ": " << msg;
      d_lock.unlock();
    }

  public:
    static constexpr int d_level = 4;

    static void DEBUG(std::string msg, std::string category){
      log(msg, category);
    }
    static void INFO(std::string msg, std::string category){
      log(msg, category);
    }
    static void ERROR(std::string msg, std::string category){
      log(msg, category);
    }
    static void WARNING(std::string msg, std::string category){
      log(msg, category);
    }
    static void FATAL(std::string msg, std::string category){
      log(msg, category);
    }

    //operator std::ostream(){
      //return d_ostream;
    //}

    //template<class T>
    //Logger& operator<<(const T& data){
      //d_ostream << data;
    //}

};


#endif
