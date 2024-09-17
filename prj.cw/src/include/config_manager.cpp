#include "config_manager.hpp"

namespace cw {

ConfigManager &ConfigManager::getInstance() {
    static ConfigManager manager;
    return manager;
}

void ConfigManager::setConfig(const char *filepath) {
    config = toml::parse_file(filepath);
}

ConfigManager::path ConfigManager::getDataDir() const {
    return {config["io"]["dataDir"].value<std::string>().value()};
}

ConfigManager::path ConfigManager::getOutDirSuffix() const {
    return {config["io"]["outDirSuffix"].value<std::string>().value()};
}

ConfigManager::path ConfigManager::getGenDirSuffix() const {
    return {config["io"]["genDirSuffix"].value<std::string>().value()};
}

double ConfigManager::getSmoothingFactor() const {
    return config["main"]["smoothingFactor"].value<double>().value();
}

int ConfigManager::getGenStrokeWidth() const {
    return config["generator"]["strokeWidth"].value<double>().value();
}

double ConfigManager::getGenStep() const {
    return config["generator"]["step"].value<double>().value();
}

double ConfigManager::getGenFOV() const {
    return config["generator"]["fov"].value<double>().value();
}

double ConfigManager::getGenInitialBound() const {
    return config["generator"]["initialBound"].value<double>().value();
}

double ConfigManager::getGenMomentumFactor() const {
    return config["generator"]["momentumFactor"].value<double>().value();
}

double ConfigManager::getGenTensionFactor() const {
    return config["generator"]["tensionFactor"].value<double>().value();
}

double ConfigManager::getGenRepelFactor() const {
    return config["generator"]["repelFactor"].value<double>().value();
}

double ConfigManager::getGenImperfectionFactor() const {
    return config["generator"]["imperfectionFactor"].value<double>().value();
}

}  // namespace cw
