#pragma once
#include <sys/types.h>
#include <unistd.h>
#include <cerrno>

namespace utils
{
    ssize_t write_all(int fd, const void* buf, size_t count);
} // namespace utils

