#include "sdb/trace.hpp"
#include "sdb/logger.hpp"
#include "utils.hpp"

sdb::StopEvent sdb::decode_wait_status(pid_t pid, int status){
    sdb::StopEvent se = {pid, sdb::StopReason::None, 0, 0, status};

    if (WIFEXITED(status)) {
        se.reason = sdb::StopReason::ExitNormally;
        se.exit_code = WEXITSTATUS(status);
    }
    else if (WIFSIGNALED(status)) {
        se.reason = sdb::StopReason::ExitBySignal;
        se.signal = WTERMSIG(status);
    }
    else if (WIFSTOPPED(status)) {
        se.reason = sdb::StopReason::SignalStop;
        se.signal = WSTOPSIG(status);
    }
    else {
        se.reason = sdb::StopReason::Unknown;
    }

    return se;
}

sdb::Result<pid_t> sdb::launch_traced_process(const std::string& program,
                                             const std::vector<std::string>& args){
    sdb::Result<pid_t> res;

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        res.error = sdb::Error{sdb::ErrorCode::SystemError, errno, strerror(errno)};
        return res;
    }

    pid_t pid = fork();

    if (pid > 0){
        res.value = pid;

        close(pipefd[1]);
        int err;
        ssize_t n;
        do {
            n = read(pipefd[0], &err, sizeof(err));
        } while (n == -1 && errno == EINTR);
        close(pipefd[0]);

        if (n == -1) {
            // read error
            res.error = sdb::Error{sdb::ErrorCode::SystemError, errno, strerror(errno)};
            res.ok = false;
        }
        else if (n == 0) {
            res.ok = true;   // exec 成功（EOF）
        }
        else if (n != sizeof(err)) {
            // 异常情况
            res.error = sdb::Error{sdb::ErrorCode::SystemError, 0, "Pipe read invalid bytes in launch_traced_process."};
            res.ok = false;
        }
        else{
            res.error = sdb::Error{sdb::ErrorCode::InternalError, err, strerror(err)};
            res.ok = false;
        }
    }
    else if (pid == 0){
        close(pipefd[0]);
        fcntl(pipefd[1], F_SETFD, FD_CLOEXEC);

        if(ptrace(PTRACE_TRACEME, 0, nullptr, nullptr)==-1){
            int err = errno;
            write(pipefd[1], &err, sizeof(err));
            log_error("Failed when calling ptrace in launch_traced_process");
            _exit(127);
        }
        std::vector<char*> argv;
        argv.reserve(args.size()+2);
        argv.push_back(const_cast<char*>(program.c_str()));
        for(const auto& s: args){
            argv.push_back(const_cast<char*>(s.c_str()));
        }
        argv.push_back(nullptr);
        if(execvp(program.c_str(), argv.data())==-1){
            int err = errno;
            utils::write_all(pipefd[1], &err, sizeof(err));
            log_error("Failed to execute new program: " + program);
            _exit(127);
        }
        res.error = sdb::Error{sdb::ErrorCode::InternalError, errno, strerror(errno)};
        res.ok = false;
    }
    else{
        close(pipefd[0]); close(pipefd[1]);
        res.error = sdb::Error{sdb::ErrorCode::SystemError, errno, strerror(errno)};
        res.ok = false;
    }

    return res;
}

sdb::Result<sdb::StopEvent> sdb::wait_initial_stop(pid_t child_pid){
    sdb::Result<sdb::StopEvent> res;

    int status = 0;
    pid_t pid = waitpid(child_pid, &status, 0);
    if(pid == -1){
        res.error = {sdb::ErrorCode::SystemError, errno, strerror(errno)};
        res.ok = false;
        return res;
    }
    
    res.value = sdb::decode_wait_status(child_pid, status);

    if(res.value.reason == sdb::StopReason::SignalStop && res.value.signal == SIGTRAP){
        res.ok = true;
    }
    else{
        res.error.code = sdb::ErrorCode::InternalError;
        res.error.message = "Unexpected initial stop";
        res.ok = false;
    }

    return res;
}