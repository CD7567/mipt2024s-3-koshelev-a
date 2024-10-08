#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>

#include "app_exception.hpp"
#include "config_manager.hpp"
#include "iohandler.hpp"
#include "transform.hpp"
#include "generator.hpp"

using namespace cw;

std::vector<int> detectEnds(const std::vector<cv::Point>& points) {
    std::vector<int> ends;

    if (points.size() > 2) {
        cv::Point prevVector = points[0] - points[points.size() - 1];
        cv::Point nextVector = points[0] - points[1];

        if ((prevVector.x * nextVector.x + prevVector.y * nextVector.y) /
                (cv::norm(prevVector) * cv::norm(nextVector)) >
            0.99) {
            ends.push_back(0);
        }
    }

    for (auto i = ++points.begin(); i + 1 < points.end(); ++i) {
        cv::Point prevVector = *i - *(i - 1);
        cv::Point nextVector = *i - *(i + 1);

        if ((prevVector.x * nextVector.x + prevVector.y * nextVector.y) /
                (cv::norm(prevVector) * cv::norm(nextVector)) >
            0.99) {
            ends.push_back(i - points.begin());
        }
    }

    if (points.size() > 2) {
        cv::Point prevVector = points[points.size() - 1] - points[points.size() - 2];
        cv::Point nextVector = points[points.size() - 1] - points[0];

        if ((prevVector.x * nextVector.x + prevVector.y * nextVector.y) /
                (cv::norm(prevVector) * cv::norm(nextVector)) >
            0.99) {
            ends.push_back(points.size() - 1);
        }
    }

    return ends;
}

int main(int argc, const char** argv) {
    // Setup sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/main.log", 1024 * 1024 * 10, 3);
    file_sink->set_level(spdlog::level::debug);

    // Setup logger
    spdlog::logger logger("cw/main", {console_sink, file_sink});

#ifndef NDEBUG
    logger.set_level(spdlog::level::debug);
#else
    logger.set_level(spdlog::level::info);
#endif

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

    logger.info("Performing smoothing");
    cv::Mat smooth = transformer.makeImageSmooth(input);

    logger.info("Extracting binary image");
    cv::Mat binary = transformer.makeBinary(smooth);

#ifndef NDEBUG
    handler.writeOutput(smooth, argv[1], "smooth");
    handler.writeOutput(binary, argv[1], "binary");
#endif

    logger.info("Detecting smoothed contour");
    auto contours = transformer.findContour(binary);
    cv::fillPoly(binary, contours[0], cv::Scalar(255, 255, 255));

    logger.info("Performing thinning");
    cv::Mat thinned;
    cv::ximgproc::thinning(binary, thinned);

#ifndef NDEBUG
    handler.writeOutput(thinned, argv[1], "thin");
#endif

    logger.info("Detecting middle line");
    auto middleLine = transformer.findContour(thinned)[0];

#ifndef NDEBUG
    int size = middleLine.size();
    for (int i = 1; i < size; ++i) {
        cv::line(input, middleLine[i - 1], middleLine[i], cv::Scalar(0, 255, 255), config.getStrokeWidth());
    }
#endif

    auto ends = detectEnds(middleLine);

    if (ends.size() < 2) {
        throw AppException("Failed to find median ends");
    }

    std::vector<cv::Point> filtered;
    int min = std::min(ends[0], ends[1]);
    int max = std::max(ends[0], ends[1]);
    for (int i = min; i <= max; ++i) {
        filtered.push_back(middleLine[i]);
    }

    middleLine = std::move(filtered);

#ifndef NDEBUG
    cv::drawMarker(input, middleLine[0], cv::Scalar(255, 255, 0), cv::MARKER_DIAMOND);
    cv::drawMarker(input, middleLine[middleLine.size() - 1], cv::Scalar(255, 255, 0), cv::MARKER_DIAMOND);

#endif

    std::vector<cv::Point> approximated;
    cv::approxPolyDP(middleLine, approximated, cv::arcLength(middleLine, false) * 0.001, false);
    middleLine = std::move(approximated);

    cv::drawContours(input, contours, 0, cv::Scalar(0, 0, 255), config.getStrokeWidth());

    auto begin = middleLine[0];
    auto end = middleLine[middleLine.size() - 1];

    double dist = std::max(
        cv::pointPolygonTest(contours[0], begin, true),
        cv::pointPolygonTest(contours[0], end, true)
    );

    auto beginAngle = angle(begin - middleLine[1]);
    auto endAngle = angle(end - middleLine[middleLine.size() - 2]);

    middleLine.insert(middleLine.begin(), begin + cv::Point(dist * cos(beginAngle), dist * sin(beginAngle)));
    middleLine.push_back(end + cv::Point(dist * cos(endAngle), dist * sin(endAngle)));

    int size = middleLine.size();
    for (int i = 1; i < size; ++i) {
        cv::line(input, middleLine[i - 1], middleLine[i], cv::Scalar(0, 255, 0), config.getStrokeWidth());
    }

    handler.writeOutput(input, argv[1]);
}
