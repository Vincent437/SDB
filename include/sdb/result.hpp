#pragma once
#include <errno.h>
#include "error.hpp"

namespace sdb{

template <typename T>
struct Result {
    T value{};
    Error error{};
    bool ok{false};
};

}