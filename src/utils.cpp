#include "utils.hpp"

ssize_t utils::write_all(int fd, const void* buf, size_t count) {
    const char* p = static_cast<const char*>(buf);
    size_t total = 0;

    while (total < count) {
        ssize_t n = write(fd, p + total, count - total);

        if (n > 0) {
            total += n;
            continue;
        }

        if (n == -1 && errno == EINTR) {
            continue; // 被信号打断，重试
        }

        return -1; // 其他错误（EPIPE 等）
    }

    return total;
}