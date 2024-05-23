#ifndef MIPT2024S_3_KOSHELEV_A_TRANSFORMER_HPP
#define MIPT2024S_3_KOSHELEV_A_TRANSFORMER_HPP

#include <spdlog/spdlog.h>

#include <opencv2/opencv.hpp>
#include <vector>

class Transformer {
  private:
    std::shared_ptr<spdlog::logger> logger;

  public:
    Transformer();

    cv::Mat makeBinary(const cv::Mat& src);

    std::vector<std::vector<cv::Point>> makeSmooth(
        const std::vector<std::vector<cv::Point>>& contours,
        double smoothingFactor);
};

#endif  // MIPT2024S_3_KOSHELEV_A_TRANSFORMER_HPP
