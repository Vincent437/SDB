#include <gtest/gtest.h>
#include "sdb/error.hpp"

TEST(ErrorTest, MakeErrorTest){

    sdb::Error err = sdb::make_error(sdb::ErrorCode::InvalidArgument, "bad arg");
    EXPECT_FALSE(err.ok());

}

TEST(ErrorTest, MakeSystemError){

    sdb::Error err = sdb::make_system_error("ptrace failed", EPERM);
    EXPECT_EQ(err.code, sdb::ErrorCode::SystemError);
    EXPECT_EQ(err.sys_errno, EPERM);
}