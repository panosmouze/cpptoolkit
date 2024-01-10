#include "CtIO.hpp"

int main() {
    CtLogSink log;
    CtFileSink file("log.txt");
    CtLogger logger(CtLogger::Level::ERROR, "TestComp");
    logger.addSink(log);
    logger.addSink(file);
    logger.log_warning("warning 1");
    logger.log_debug("debug 1");
    logger.log_error("error 1");
    logger.log_warning("warning 2");
    logger.log_info("info 1");
    logger.log_info("info 2");
    logger.log_critical("critical 1");
    return 0;
}
