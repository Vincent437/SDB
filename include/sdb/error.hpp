#pragma once
#include <string>
#include <errno.h>

namespace sdb {

enum class ErrorCode {
    Ok = 0,
    InvalidArgument,
    SystemError,
    NotImplemented,
    InternalError
};

struct Error {
    ErrorCode code{ErrorCode::Ok};
    int sys_errno{0};
    std::string message;

    bool ok() const noexcept { return code == ErrorCode::Ok; }
};

template <typename T>
struct Result {
    T value{};
    Error error{};
    bool ok{false};
};

inline Error make_system_error(const std::string& msg, int err){
    return Error{ErrorCode::SystemError, err, msg};
}

inline Error make_error(ErrorCode code, const std::string& msg){
    return Error{code,0,msg};
}

} // namespace sdb