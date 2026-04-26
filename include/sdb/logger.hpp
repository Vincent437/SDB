#pragma once
#include <string>
#include <iostream>

namespace sdb {

enum class LogLevel {
    Error = 0,
    Info,
    Debug
};

inline LogLevel g_log_level{LogLevel::Info};

inline void set_log_level(LogLevel level){
    g_log_level = level;
}

inline LogLevel get_log_level(){
    return g_log_level;
}

inline void log_error(const std::string& msg){
    // error永远输出
    std::cerr<<"[ERROR] "<<msg<<std::endl;
}

inline void log_info(const std::string& msg){
    if(get_log_level()<LogLevel::Info) return;
    std::cout<<"[INFO] "<<msg<<std::endl;
}

inline void log_debug(const std::string& msg){
    if(get_log_level()<LogLevel::Debug) return;
    std::cout<<"[DEBUG] "<<msg<<std::endl;
}

} // namespace sdb