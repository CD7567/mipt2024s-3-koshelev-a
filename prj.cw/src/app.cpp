#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <filesystem>
#include <opencv4/opencv2/opencv.hpp>

int main(int argc, const char** argv) {
    // Configure sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/log.log", 1024 * 1024 * 10, 3);
    file_sink->set_level(spdlog::level::debug);

    // Configure logger
    spdlog::logger logger("prj.cw", {console_sink, file_sink});
    logger.set_level(spdlog::level::debug);
}
