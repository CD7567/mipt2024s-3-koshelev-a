#include "transform.hpp"

#include "app_exception.hpp"
#include "config_manager.hpp"

namespace cw {

Transformer::Transformer() : logger(spdlog::default_logger()) {}

cv::Mat Transformer::makeBinary(const cv::Mat& src) {
    logger->info("Creating greyscale image");
    cv::Mat grayScale;
    cv::cvtColor(src, grayScale, cv::COLOR_BGR2GRAY);

    logger->info("Transforming to binary image");

    cv::Mat binary;
    cv::threshold(grayScale, binary, 127, 255, cv::THRESH_BINARY);

    if (binary.at<uchar>(0, 0) == 255) {
        cv::threshold(grayScale, binary, 127, 255, cv::THRESH_BINARY_INV);
    }

    return binary;
}

cv::Mat Transformer::makeImageSmooth(const cv::Mat& src) {
    auto& config = ConfigManager::getInstance();
    cv::Mat result;

    cv::medianBlur(src, result, config.getKernelSize());

    return result;
}

std::vector<std::vector<cv::Point>> Transformer::findContour(const cv::Mat& src) {
    logger->info("Detecting contours");
    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(src, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    logger->debug("Detected amount of contours: {}", contours.size());

    contours.resize(1);
    return contours;
}

}  // namespace cw
