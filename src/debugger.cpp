#include "sdb/debugger.hpp"
#include "sdb/logger.hpp"

bool sdb::Debugger::launch(const std::string& program, const std::vector<std::string>& args){
    if(state_ != sdb::DebuggerState::Idle && state_ != sdb::DebuggerState::Exited){
        state_ = sdb::DebuggerState::Error;
        last_error_ = sdb::Error{sdb::ErrorCode::InternalError, 0, "Failed to launch " + program};
        return false;
    }

    auto launch_res = sdb::launch_traced_process(program, args);

    if (!launch_res.ok){
        if(launch_res.value>0) waitpid(launch_res.value, nullptr, 0);
        state_ = sdb::DebuggerState::Error;
        last_error_ = launch_res.error;
        return false;
    }

    pid_ = launch_res.value;

    auto wait_res = sdb::wait_initial_stop(pid_);

    if(wait_res.ok){
        state_ = sdb::DebuggerState::Stopped;
        last_event_ = wait_res.value;
        return true;
    }
    else{
        if((wait_res.value.reason == sdb::StopReason::SignalStop 
            || wait_res.value.reason == sdb::StopReason::None) 
            && pid_>0){
            kill(pid_, SIGTERM);
            waitpid(pid_, nullptr, 0);
        }
        state_ = sdb::DebuggerState::Error;
        last_error_ = wait_res.error;
        return false;
    }
}