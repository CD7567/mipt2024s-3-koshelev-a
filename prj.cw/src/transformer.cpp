#include "transformer.hpp"

Transformer::Transformer() : logger(spdlog::default_logger()) {}

cv::Mat Transformer::makeBinary(const cv::Mat& src) {
    logger->info("Creating greyscale image");
    cv::Mat grayScale;
    cv::cvtColor(src, grayScale, cv::COLOR_BGR2GRAY);

    logger->info("Transforming to binary image");
    cv::Mat binary;
    cv::threshold(grayScale, binary, 127, 255, cv::THRESH_BINARY_INV);

    return binary;
}

std::vector<std::vector<cv::Point>> Transformer::makeSmooth(
    const std::vector<std::vector<cv::Point>>& contours,
    double smoothingFactor) {
    std::vector<std::vector<cv::Point>> smoothed{contours.size()};

    for (size_t i = 0; i < contours.size(); i++) {
        approxPolyDP(contours[i], smoothed[i],
                     arcLength(contours[i], true) * smoothingFactor, true);
    }

    return smoothed;
}
