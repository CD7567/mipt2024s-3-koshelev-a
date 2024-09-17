#include "generator.hpp"

#include <spdlog/spdlog.h>

#include <random>

#include "config_manager.hpp"

namespace cw {

/**
 * Calculate polar angle of a vector
 *
 * @param vector Source vector
 * @return Polar angle in radians
 */
inline double angle(const cv::Point2d& vector) {
    double angle = acos(vector.x / cv::norm(vector));

    if (vector.y < 0) {
        angle = 2 * CV_PI - angle;
    }

    return angle;
}

/**
 * Calculate tension weight for direction correction
 *
 * @param point Current point
 * @param width Image width
 * @param height Image height
 * @return Tension magnitude in [0.0, 1.0]
 */
inline double getTensionMagnitude(cv::Point2d point, int width, int height) {
    // Center point
    point -= {width / 2.0, height / 2.0};

    return std::min(ConfigManager::getInstance().getGenTensionFactor(), 1.0) *
           std::min((4 * point.x * point.x / (width * width) +
                    4 * point.y * point.y / (height * height)),
                    1.0);
}

/**
 * Calculate tension vector for direction correction
 *
 * @param point Current point
 * @param width Image width
 * @param height Image height
 * @return Tension direction
 */
inline cv::Point2d getTensionVector(cv::Point2d point, int width,
                                    int height) {
    point -= {width / 2.0, height / 2.0};

    cv::Point2d result = {- point.x / (width * width), - point.y / (height * height)};

    return result /= cv::norm(result);
}

/**
 * Calculate repel vector for direction correction
 *
 * @param points Current points
 * @return Repel direction
 */
inline cv::Point2d getRepelVector(const std::vector<cv::Point2d>& points) {
    auto last = --points.cend();
    cv::Point2d result;

    for (auto it = points.cbegin(); it < last; ++it) {
        cv::Point2d tmp = *last - *it;
        double norm = cv::norm(tmp);

        result += tmp / (norm * norm);
    }

    return result /= cv::norm(result);
}

void generateLine(std::vector<cv::Point2d>& dest,
                  std::vector<std::vector<cv::Point2d>>& dir, int maxWidth,
                  int maxHeight, int number) {
    auto& config = ConfigManager::getInstance();

    double step = config.getGenStep();
    double fov = config.getGenFOV() * CV_PI;
    double bound = config.getGenInitialBound();

    std::random_device random_device;
    std::mt19937 generator(random_device());

    std::uniform_int_distribution<int> widthDistribution(
        bound * maxWidth, (1 - bound) * maxWidth);
    std::uniform_int_distribution<int> heightDistribution(
        bound * maxHeight, (1 - bound) * maxHeight);
    std::uniform_real_distribution<double> angleDistribution(-fov, fov);

    dest.emplace_back(widthDistribution(generator),
                      heightDistribution(generator));
    double initialAngle =
        std::uniform_real_distribution<double>(-CV_PI, CV_PI)(generator);
    dest.push_back(dest.back() + cv::Point2d(step * cos(initialAngle),
                                             step * sin(initialAngle)));

    double momentum = std::min(config.getGenMomentumFactor(), 1.0);
    double repel = std::min(config.getGenRepelFactor(), 1.0);

    for (int i = 2; i < number; ++i) {
        spdlog::default_logger()->info("Generating section {}", i);

        cv::Point2d prevPoint = dest[i - 1];

        cv::Point2d prevVector = prevPoint - dest[i - 2];
        prevVector /= cv::norm(prevVector);

        cv::Point2d tensionVector = getTensionVector(prevPoint, maxWidth, maxHeight);
        cv::Point2d repelVector = getRepelVector(dest);

        double tension = getTensionMagnitude(prevPoint, maxWidth, maxHeight);

        cv::Point2d newVector = (momentum * prevVector + repel * repelVector) / (momentum + repel);
        newVector = (1 - tension) * newVector + tension * tensionVector;

        spdlog::default_logger()->debug("tension {}", tension);

        std::vector<cv::Point2d> curr(4);

        double newAngle = angle(newVector);

        double prevAngle = angle(prevVector);
        double tensionAngle = angle(tensionVector);
        double repelAngle = angle(repelVector);

        curr[0] = {cos(prevAngle), sin(prevAngle)};
        curr[1] = {cos(tensionAngle), sin(tensionAngle)};
        curr[2] = {cos(repelAngle), sin(repelAngle)};
        curr[3] = {cos(newAngle), sin(newAngle)};

        dir.emplace_back(curr);

        std::uniform_real_distribution<double> dynAngleDistribution(
            newAngle - fov, newAngle + fov);
        double angle = dynAngleDistribution(generator);
        dest.push_back(prevPoint +
                       cv::Point2d(step * cos(angle), step * sin(angle)));
    }
}

}  // namespace cw
