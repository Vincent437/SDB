#pragma once
#include <string>
#include <sys/types.h>

namespace sdb{
enum class DebuggerState {
    Idle,
    Running,
    Stopped,
    Exited,
    Error
};

enum class StopReason {
    None,
    SignalStop,
    ExitNormally,
    ExitBySignal,
    PtraceEvent,
    Unknown
};

struct StopEvent {
    pid_t pid = -1;
    StopReason reason = StopReason::None;
    int signal = 0;      // WSTOPSIG or termsig
    int exit_code = 0;   // WEXITSTATUS
    int raw_status = 0;  // waitpid status
};
} // namespace sdb