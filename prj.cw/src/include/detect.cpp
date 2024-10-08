#include "detect.hpp"

#include "app_exception.hpp"
#include "generator.hpp"
#include "iohandler.hpp"
#include "transform.hpp"

namespace cw {

/**
 * Detect ends of a contour if a contour is a single line
 *
 * @param points contour
 * @return Indices of ends
 */
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

/**
 * Detect smoothed contour of an elongated shape
 *
 * @param src Source image
 * @return Detected contours
 */
std::vector<std::vector<cv::Point>> detectSmoothedContour(const cv::Mat& src) {
    auto logger = spdlog::default_logger();
    Transformer transformer{};

    logger->info("Performing smoothing");
    cv::Mat smooth = transformer.makeImageSmooth(src);

    logger->info("Extracting binary image");
    cv::Mat binary = transformer.makeBinary(smooth);

#ifndef NDEBUG
    IOHandler handler{};
    handler.writeOutput(smooth, argv[1], "smooth");
    handler.writeOutput(binary, argv[1], "binary");
#endif

    logger->info("Detecting smoothed contour");
    return transformer.findContour(binary);
}

/**
 * Detect median line of an elongated shape
 *
 * @param src Source image
 * @param contours Contour[0] is used as a shape border
 * @return Detected median line
 */
std::vector<cv::Point> detectMedian(const cv::Mat& src, const std::vector<std::vector<cv::Point>> contours) {
    auto logger = spdlog::default_logger();
    Transformer transformer{};

    logger->info("Performing smoothing");
    cv::Mat smooth = transformer.makeImageSmooth(src);

    logger->info("Extracting binary image");
    cv::Mat binary = transformer.makeBinary(smooth);

    cv::fillPoly(binary, contours[0], cv::Scalar(255, 255, 255));

    logger->info("Performing thinning");
    cv::Mat thinned;
    cv::ximgproc::thinning(binary, thinned);

#ifndef NDEBUG
    IOHandler handler{};
    handler.writeOutput(thinned, argv[1], "thin");
#endif

    logger->info("Detecting middle line");
    auto median = transformer.findContour(thinned)[0];

    logger->info("Detecting ends");
    auto ends = detectEnds(median);

    if (ends.size() < 2) {
        logger->error("Failed to find median ends");
        throw AppException("Failed to find median ends");
    }

    std::vector<cv::Point> filtered;
    int min = std::min(ends[0], ends[1]);
    int max = std::max(ends[0], ends[1]);
    for (int i = min; i <= max; ++i) {
        filtered.push_back(median[i]);
    }

    median = std::move(filtered);

    logger->info("Approximating contour");
    std::vector<cv::Point> approximated;
    cv::approxPolyDP(median, approximated, cv::arcLength(median, false) * 0.001, false);
    median = std::move(approximated);

    auto begin = median[0];
    auto end = median[median.size() - 1];

    double dist = std::max(
        cv::pointPolygonTest(contours[0], begin, true),
        cv::pointPolygonTest(contours[0], end, true)
    );

    auto beginAngle = angle(begin - median[1]);
    auto endAngle = angle(end - median[median.size() - 2]);

    median.insert(median.begin(), begin + cv::Point(dist * cos(beginAngle), dist * sin(beginAngle)));
    median.push_back(end + cv::Point(dist * cos(endAngle), dist * sin(endAngle)));

#ifndef NDEBUG
    cv::drawMarker(thinned, median[0], cv::Scalar(255, 255, 0), cv::MARKER_DIAMOND);
    cv::drawMarker(thinned, median[median.size() - 1], cv::Scalar(255, 255, 0), cv::MARKER_DIAMOND);
    handler.writeOutput(thinned, argv[1], "ends");
#endif

    return median;
}

}