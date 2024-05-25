#include "iohandler.hpp"

#include <string>

#include "app_exception.hpp"
#include "config_manager.hpp"

IOHandler::IOHandler(int argc, const char **argv)
    : logger(spdlog::default_logger()) {
    logger->info("Parsing command line arguments");

    if (argc < 2) {
        logger->error("Expected {} arguments but got {}", 2, argc);
        throw AppException("Incorrect amount of arguments");
    }

    auto& config = ConfigManager::getInstance();
    auto dataDir = config.getDataDir();

    outDir = config.getOutDirSuffix();
    inFile = std::filesystem::path(argv[1]);

    inFile = dataDir / inFile;
    outDir = dataDir / outDir;

    if (!exists(outDir)) {
        logger->debug("No output directory found, creating");
        create_directory(outDir);
    }
}

cv::Mat IOHandler::readInput() {
    logger->info("Reading input file: {}", inFile.string());

    return cv::imread(inFile);
}

void IOHandler::writeImage(cv::Mat &img, const char *suffix) {
    std::string stem = inFile.stem();
    std::string extension = inFile.extension();
    std::filesystem::path imagePath =
        outDir / (stem + "_" + suffix + extension);

    logger->info("Writing output file: {}", imagePath.string());
    cv::imwrite(imagePath, img);
}
