#pragma once
#include <string>
#include <cstring>
#include <vector>
#include "error.hpp"
#include "logger.hpp"

namespace sdb {

struct AppConfig {
public:
    LogLevel log_level{LogLevel::Info};
    bool show_help{false};
    std::string target_program;
    std::vector<std::string> target_args;
};

Result<AppConfig> parse_args(int argc, const char** argv);

} // namespace sdb