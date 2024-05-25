#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <opencv2/opencv.hpp>

#include "config_manager.hpp"
#include "iohandler.hpp"
#include "transform.hpp"

int main(int argc, const char** argv) {
    // Setup sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/log.log", 1024 * 1024 * 10, 3);
    file_sink->set_level(spdlog::level::debug);

    // Setup logger
    spdlog::logger logger("prj.cw", {console_sink, file_sink});
    logger.set_level(spdlog::level::debug);
    spdlog::set_default_logger(std::make_unique<spdlog::logger>(logger));

    logger.info("===== [Starting new run] =====");

    // Setup config manager
    auto& config = ConfigManager::getInstance();
    config.setConfig("config.toml");

    // Handle input
    IOHandler handler{argc, argv};
    cv::Mat input = handler.readInput();

    // Initialize transformer
    Transformer transformer{};

    cv::Mat binary = transformer.makeBinary(input);

    logger.info("Detecting contours");
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    logger.debug("Detected amount of contours: {}", contours.size());

    cv::Mat contourImage(binary.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);

    logger.info("Creating raw contour image");
    cv::Mat rawContourImage(binary.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    for (size_t i = 0; i < contours.size(); i++) {
        cv::drawContours(rawContourImage, contours, i, colors[i % 3]);
    }
    handler.writeImage(rawContourImage, "raw");

    auto smoothedContours = transformer.makeSmooth(contours);

    logger.info("Creating smooth contour image");
    cv::Mat smoothContourImage(binary.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    for (size_t i = 0; i < contours.size(); ++i) {
        cv::drawContours(smoothContourImage, smoothedContours, i,
                         colors[i % 3]);
    }
    handler.writeImage(smoothContourImage, "smooth");

    /*
    cv::namedWindow("Img show");
    cv::imshow("Img show", input);

    cv::waitKey(0);

    cv::destroyAllWindows();
    */
}
