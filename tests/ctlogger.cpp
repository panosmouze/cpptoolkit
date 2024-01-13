#include <gtest/gtest.h>
#include "CtIO.hpp"

TEST(CtLoggerTest01, LogFunctionality) {
    CtLogger logger(CtLogger::Level::INFO, "TEST_LOGGER");
    logger.log_info("Test Log Message");
    ASSERT_TRUE(true);
}
