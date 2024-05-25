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

}  // namespace cw
