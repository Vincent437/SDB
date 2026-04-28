#include <gtest/gtest.h>
#include "sdb/debugger.hpp"

TEST(DebuggerTest, LaunchSuccess) {
    sdb::Debugger dbg{};

    auto res = dbg.launch("/bin/echo", {"hello"});

    EXPECT_TRUE(res);
    EXPECT_EQ(dbg.state(), sdb::DebuggerState::Stopped);
    EXPECT_GT(dbg.pid(),0);
}

TEST(DebuggerTest, LaunchFailure) {
    sdb::Debugger dbg{};

    auto res = dbg.launch("/bin/echo", {"hello"});
    res = dbg.launch("/bin/echo", {"hello"});

    EXPECT_FALSE(res);
    EXPECT_EQ(dbg.state(), sdb::DebuggerState::Error);
}