#ifndef MIPT2024S_3_KOSHELEV_A_TRANSFORM_HPP
#define MIPT2024S_3_KOSHELEV_A_TRANSFORM_HPP

#include <spdlog/spdlog.h>

#include <opencv2/opencv.hpp>
#include <vector>

namespace cw {

class Transformer {
  private:
    std::shared_ptr<spdlog::logger> logger;

  public:
    Transformer();

    cv::Mat makeBinary(const cv::Mat& src);

    cv::Mat makeImageSmooth(const cv::Mat& src);

    std::vector<std::vector<cv::Point>> findContour(const cv::Mat& src);
};

}  // namespace cw

#endif  // MIPT2024S_3_KOSHELEV_A_TRANSFORM_HPP
