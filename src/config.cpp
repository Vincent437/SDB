#include "sdb/config.hpp"

namespace sdb{

Result<AppConfig> parse_args(int argc, const char** argv){
    Result<AppConfig> res;
    if(argc<=0) return res;

    bool parsing_debugger_args = true;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        // 第一个非 option -> 切换到 target
        if (parsing_debugger_args && !arg.empty() && arg[0] != '-') {
            parsing_debugger_args = false;

            // 当前这个就是 target program
            res.value.target_program = arg;
            continue;
        }

        if (!parsing_debugger_args) {
            // target program 的所有参数：原样保存
            res.value.target_args.push_back(arg);
            continue;
        }

        // ===== debugger 参数解析 =====
        if (arg == "--help") {
            res.value.show_help = true;
        }
        else if (arg.rfind("--log-level=", 0) == 0) {
            std::string level = arg.substr(strlen("--log-level="));

            if (level == "error") res.value.log_level = LogLevel::Error;
            else if (level == "info") res.value.log_level = LogLevel::Info;
            else if (level == "debug") res.value.log_level = LogLevel::Debug;
            else {
                res.error.code = ErrorCode::InvalidArgument;
                res.error.message = "Invalid argument " + arg + " for log-level!";
                log_error(res.error.message);
                break;
            }
        }
        else {
            res.error.code = ErrorCode::InvalidArgument;
            res.error.message = "Invalid argument " + arg + " for debugger!";
            log_error(res.error.message);
            break;
        }
    }
    return res;
}

} // namespace sdb