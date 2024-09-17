#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <cmath>
#include <random>
#include <vector>

#include "app_exception.hpp"
#include "config_manager.hpp"
#include "generator.hpp"
#include "iohandler.hpp"

using namespace cw;

int main(int argc, const char** argv) {
    // Setup sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/gen.log", 1024 * 1024 * 10, 3);
    file_sink->set_level(spdlog::level::debug);

    // Setup logger
    spdlog::logger logger("cw/gen", {console_sink, file_sink});

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

    if (argc < 5) {
        logger.error("Expected at least {} arguments, but got {}!", 5, argc);
        throw AppException("Incorrect number of arguments!");
    }

    // Handle input
    IOHandler handler{};

    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);
    int numberOfPoints = std::stoi(argv[3]);

    std::vector<cv::Point2d> points;
    std::vector<std::vector<cv::Point2d>> trace;

    generateLine(points, trace, width, height, numberOfPoints);

    cv::Mat generatedImage(cv::Size(width, height), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Scalar white{255, 255, 255};

    for (size_t i = 1; i < numberOfPoints; ++i) {
        cv::line(generatedImage, points[i - 1], points[i], cv::Scalar(255, 255, 255), config.getGenStrokeWidth());
    }

#ifndef NDEBUG
    for (int i = 0; i < trace.size(); ++i) {
        cv::line(generatedImage, points[i + 1], points[i + 1] + 20 * trace[i][0], cv::Scalar(255, 0, 0), 2);
        cv::line(generatedImage, points[i + 1], points[i + 1] + 20 * trace[i][1], cv::Scalar(0, 255, 0), 2);
        cv::line(generatedImage, points[i + 1], points[i + 1] + 20 * trace[i][2], cv::Scalar(0, 0, 255), 2);
        cv::line(generatedImage, points[i + 1], points[i + 1] + 20 * trace[i][3], cv::Scalar(255, 0, 255), 2);
    }
#endif

    handler.writeGenerated(generatedImage, argv[4], "gen");
}