#include <gtest/gtest.h>
#include <sdb/config.hpp>

TEST(ConfigTest, HelpTest){
    const char* argv[] = {
        "sdb",
        "--help"
    };

    sdb::Result<sdb::AppConfig> res = sdb::parse_args(2, argv);

    EXPECT_TRUE(res.value.show_help);
}

TEST(ConfigTest, LoglevelTest){
    const char* argv[] = {
        "sdb",
        "--log-level=debug",
        "/bin/ls",
        "-l"
    };

    sdb::Result<sdb::AppConfig> res = sdb::parse_args(4, argv);

    EXPECT_EQ(res.value.log_level, sdb::LogLevel::Debug);
    EXPECT_EQ(res.value.target_program, "/bin/ls");
    EXPECT_EQ(res.value.target_args, std::vector<std::string>{"-l"});
}

TEST(ConfigTest, InvalidArgTest){
    const char* argv[] = {
        "sdb",
        "--log-level=abc",
    };

    sdb::Result<sdb::AppConfig> res = sdb::parse_args(2, argv);

    EXPECT_FALSE(res.error.ok());
    EXPECT_EQ(res.error.code, sdb::ErrorCode::InvalidArgument);
}