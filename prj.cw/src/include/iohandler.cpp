#include "iohandler.hpp"

#include <string>

#include "config_manager.hpp"

namespace cw {

IOHandler::IOHandler() : logger(spdlog::default_logger()) {
    logger->info("Parsing command line arguments");

    auto &config = ConfigManager::getInstance();

    dataDir = config.getDataDir();
    outDir = dataDir / config.getOutDirSuffix();
    genDir = dataDir / config.getGenDirSuffix();

    if (!exists(outDir)) {
        logger->debug("No output directory found, creating");
        create_directories(outDir);
    }

    if (!exists(genDir)) {
        logger->debug("No generated directory found, creating");
        create_directories(genDir);
    }
}

cv::Mat IOHandler::readInput(const char *filename) {
    std::filesystem::path inFile = dataDir / filename;

    logger->info("Reading input file: {}", inFile.string());

    return cv::imread(inFile);
}

void IOHandler::writeOutput(cv::Mat &img, const char *filename,
                            const char *suffix) {
    std::filesystem::path inFilename{filename};
    std::filesystem::path imagePath =
        outDir / (inFilename.stem().string() + "_" + suffix +
                  inFilename.extension().string());

    logger->info("Writing output file: {}", imagePath.string());
    cv::imwrite(imagePath, img);
}

void IOHandler::writeGenerated(cv::Mat &img, const char *filename,
                               const char *suffix) {
    std::filesystem::path inFilename{filename};
    std::filesystem::path imagePath =
        genDir / (inFilename.stem().string() + "_" + suffix +
                  inFilename.extension().string());

    logger->info("Writing output file: {}", imagePath.string());
    cv::imwrite(imagePath, img);
}

}  // namespace cw
