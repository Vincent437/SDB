#include <gtest/gtest.h>
#include <sdb/trace.hpp>

TEST(LaunchTest, LaunchTracedProcessSuccess) {
    std::string program = "/bin/echo";
    std::vector<std::string> args = {"hello"};

    auto res = sdb::launch_traced_process(program, args);

    EXPECT_TRUE(res.ok);
    EXPECT_GT(res.value, 0);
}

TEST(LaunchTest, LaunchTracedProcessFailure) {
    std::string program = "/not/exist";

    auto res = sdb::launch_traced_process(program, {});

    EXPECT_TRUE(res.ok);
    EXPECT_GT(res.value, 0);
}
