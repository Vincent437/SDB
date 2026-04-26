#include <gtest/gtest.h>
#include "sdb/logger.hpp"

TEST(LogTest, LogDebugWhenInfo){
    sdb::set_log_level(sdb::LogLevel::Info);
    testing::internal::CaptureStdout();
    sdb::log_debug("x");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.substr(0,7), "[DEBUG]");
}

TEST(LogTest, LogDebugWhenDebug){
    sdb::set_log_level(sdb::LogLevel::Debug);
    testing::internal::CaptureStdout();
    sdb::log_debug("x");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.substr(0,7), "[DEBUG]");
}