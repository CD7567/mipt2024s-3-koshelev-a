#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <opencv2/ximgproc.hpp>
#include "app_exception.hpp"
#include "config_manager.hpp"
#include "iohandler.hpp"
#include "detect.hpp"

using namespace cw;

int main(int argc, const char** argv) {
    // Setup sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/main.log", 1024 * 1024 * 10, 3);
    file_sink->set_level(spdlog::level::debug);

    // Setup logger
    spdlog::logger logger("cw/main", {console_sink, file_sink});

#ifndef NDEBUG
    logger.set_level(spdlog::level::debug);
#else
    logger.set_level(spdlog::level::info);
#endif

    spdlog::set_default_logger(std::make_unique<spdlog::logger>(logger));

    logger.info("===== [Starting new run] =====");

    // Setup config manager
    auto& config = ConfigManager::getInstance();
    config.setConfig("config.toml");

    if (argc < 2) {
        logger.error("Expected at least {} arguments, but got {}!", 2, argc);
        throw AppException("Incorrect number of arguments!");
    }

    // Handle input
    IOHandler handler{};
    cv::Mat input = handler.readInput(argv[1]);

    auto contours = detectSmoothedContour(input);
    auto median = detectMedian(input, contours);

    cv::drawContours(input, contours, 0, cv::Scalar(0, 0, 255), config.getStrokeWidth());

    int size = median.size();
    for (int i = 1; i < size; ++i) {
        cv::line(input, median[i - 1], median[i], cv::Scalar(0, 255, 0), config.getStrokeWidth());
    }

    handler.writeOutput(input, argv[1]);
}
