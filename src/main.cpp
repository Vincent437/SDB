#include <iostream>
#include <string>
#include <unordered_map>
#include "sdb/logger.hpp"
#include "sdb/config.hpp"
#include "sdb/debugger.hpp"

int main(int argc, const char** argv){
    std::cout<<"sdb 0.1.0"<<std::endl;

    auto parse_res = sdb::parse_args(argc, argv);

    if(!parse_res.ok){
        sdb::log_error("Parsing cmd failed: " + parse_res.error.message);
        return 1;
    }

    sdb::g_log_level = parse_res.value.log_level;
    if(parse_res.value.show_help) sdb::show_help();

    sdb::Debugger dbg{};
    if(!dbg.launch(parse_res.value.target_program, parse_res.value.target_args)){
        sdb::log_error("Failed to launch "+parse_res.value.target_program+". Reason: "+dbg.last_error().message);
        return 1;
    }

    sdb::log_debug("attached pid = "+std::to_string(dbg.pid())+"\n" + 
                    "initial stop: SIGTRAP\n" + 
                    "state=Stopped");
    

    std::string input;
    
    while(true){

        std::cin>>input;

        if(input == "quit" || input == "q") break;

        sdb::log_info("command not implemented");
    }

    return 0;
}