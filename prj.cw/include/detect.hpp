#ifndef MIPT2024S_3_KOSHELEV_A_DETECT_HPP
#define MIPT2024S_3_KOSHELEV_A_DETECT_HPP

#include <opencv2/ximgproc.hpp>
#include <vector>
#include <spdlog/spdlog.h>

namespace cw {

std::vector<std::vector<cv::Point>> detectSmoothedContour(const cv::Mat& src);

std::vector<cv::Point> detectMedian(const cv::Mat& src, const std::vector<std::vector<cv::Point>> contours);

}

#endif  // MIPT2024S_3_KOSHELEV_A_DETECT_HPP
