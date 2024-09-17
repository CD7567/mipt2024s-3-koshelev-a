#ifndef MIPT2024S_3_KOSHELEV_A_IOHANDLER_HPP
#define MIPT2024S_3_KOSHELEV_A_IOHANDLER_HPP

#include <spdlog/spdlog.h>

#include <filesystem>
#include <opencv2/opencv.hpp>

namespace cw {

class IOHandler {
  private:
    std::filesystem::path dataDir;
    std::filesystem::path outDir;
    std::filesystem::path genDir;

    std::shared_ptr<spdlog::logger> logger;

  public:
    IOHandler();

    cv::Mat readInput(const char* filename);

    void writeOutput(cv::Mat& img, const char* filename, const char* suffix);
    void writeGenerated(cv::Mat& img, const char* filename, const char* suffix);
};

}  // namespace cw

#endif  // MIPT2024S_3_KOSHELEV_A_IOHANDLER_HPP
