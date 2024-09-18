#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <opencv2/opencv.hpp>

#include "app_exception.hpp"
#include "config_manager.hpp"
#include "iohandler.hpp"
#include "transform.hpp"

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
    logger.set_level(spdlog::level::debug);
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

    // Initialize transformer
    Transformer transformer{};

    cv::Mat smooth = transformer.makeImageSmooth(input);
    cv::Mat binary = transformer.makeBinary(smooth);

    handler.writeOutput(smooth, argv[1], "smooth");

    auto contours = transformer.findContour(binary);

    cv::drawContours(input, contours, 0, cv::Scalar(0, 0, 255), config.getStrokeWidth());

    handler.writeOutput(input, argv[1], "raw");
}
