#ifndef MIPT2024S_3_KOSHELEV_A_GENERATOR_HPP
#define MIPT2024S_3_KOSHELEV_A_GENERATOR_HPP

#include <opencv2/opencv.hpp>

namespace cw {

void generateLine(std::vector<cv::Point2d>& dest,
                  std::vector<std::vector<cv::Point2d>>& dir, int maxWidth,
                  int maxHeight, int number);

void makeImperfections(cv::Mat& image);

}  // namespace cw

#endif  // MIPT2024S_3_KOSHELEV_A_GENERATOR_HPP
