#pragma once
#include <string>
#include <vector>
#include <signal.h>
#include "sdb/types.hpp"
#include "sdb/trace.hpp"

namespace sdb{

class Debugger {
public:
    bool launch(const std::string& program, const std::vector<std::string>& args);
    DebuggerState state() const noexcept {return state_;}
    pid_t pid() const noexcept {return pid_;}
    const StopEvent& last_event() const noexcept {return last_event_;}
    const Error& last_error() const noexcept {return last_error_;}

private:
    pid_t pid_ = -1;
    DebuggerState state_ = DebuggerState::Idle;
    StopEvent last_event_{};
    Error last_error_{};
};

}