#include <random>

#include "config_manager.hpp"
#include "generator.hpp"

namespace cw {

void generateLine(std::vector<cv::Point>& dest, int maxWidth, int maxHeight,
                    int number) {
    auto& config = ConfigManager::getInstance();

    double step = config.getGenStep();
    double fov = config.getGenFOV();
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
        std::uniform_real_distribution<double>(-fov, fov)(generator);
    dest.push_back(dest.back() + cv::Point(step * cos(initialAngle),
                                           step * sin(initialAngle)));

    for (int i = 2; i < number; ++i) {
        cv::Point prevVector = dest[i - 1] - dest[i - 2];
        double prevAngle = acos(prevVector.x / cv::norm(prevVector));

        if (prevVector.y < 0) {
            prevAngle = -prevAngle;
        }

        std::uniform_real_distribution<double> dynAngleDistribution(
            prevAngle - fov, prevAngle + fov);
        double angle = angleDistribution(generator);
        dest.push_back(dest.back() +
                       cv::Point(step * cos(angle), step * sin(angle)));
    }
}

}  // namespace cw
