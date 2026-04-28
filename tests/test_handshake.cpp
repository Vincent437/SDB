#include <gtest/gtest.h>
#include <iostream>
#include "sdb/trace.hpp"

TEST(HandshakeTest, HandshakeSuccess) {
    std::string program = "/bin/echo";
    std::vector<std::string> args = {"hello"};

    auto launch_res = sdb::launch_traced_process(program, args);

    EXPECT_TRUE(launch_res.ok);
    EXPECT_GT(launch_res.value, 0);

    auto res = sdb::wait_initial_stop(launch_res.value);

    EXPECT_TRUE(res.ok);
    EXPECT_EQ(res.value.reason, sdb::StopReason::SignalStop);
    EXPECT_EQ(res.value.signal, SIGTRAP);
}

TEST(HandshakeTest, HandshakeFailure) {
    std::string program = "/not/exist";

    auto launch_res = sdb::launch_traced_process(program, {});

    EXPECT_TRUE(launch_res.ok);
    EXPECT_GT(launch_res.value, 0);

    auto res = sdb::wait_initial_stop(launch_res.value);

    std::cout<< res.error.message <<std::endl;
    EXPECT_FALSE(res.ok);

}
