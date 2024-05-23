#ifndef MIPT2024S_3_KOSHELEV_A_IOHANDLER_HPP
#define MIPT2024S_3_KOSHELEV_A_IOHANDLER_HPP

#include <spdlog/spdlog.h>

#include <filesystem>
#include <opencv2/opencv.hpp>

class IOHandler {
  private:
    std::filesystem::path dataDir;
    std::filesystem::path inFile;
    std::filesystem::path outDir;

    std::shared_ptr<spdlog::logger> logger;

  public:
    IOHandler(int argc, const char** argv);

    cv::Mat readInput();

    void writeImage(cv::Mat& img, const char* suffix);
};

#endif  // MIPT2024S_3_KOSHELEV_A_IOHANDLER_HPP
