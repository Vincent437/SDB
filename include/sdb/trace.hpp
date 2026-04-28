#pragma once
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>
#include "sdb/types.hpp"
#include "sdb/result.hpp"

namespace sdb{

using LaunchResult = Result<pid_t>;
using HandshakeResult = Result<StopEvent>;

StopEvent decode_wait_status(pid_t pid, int status);

LaunchResult launch_traced_process(const std::string& program,
                                   const std::vector<std::string>& args);

HandshakeResult wait_initial_stop(pid_t child_pid);

}