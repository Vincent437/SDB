#include <iostream>
#include <string>
#include <unordered_map>
#include "sdb/config.hpp"

int main(int argc, const char** argv){
    std::cout<<"sdb 0.1.0"<<std::endl;

    auto res = sdb::parse_args(argc, argv);

    if(!res.ok){
        sdb::log_error("Parsing cmd failed!");
        return 1;
    }

    sdb::g_log_level = res.value.log_level;

    return 0;
}