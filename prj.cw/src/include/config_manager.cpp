#include "config_manager.hpp"

ConfigManager &ConfigManager::getInstance() {
    static ConfigManager manager;
    return manager;
}

void ConfigManager::setConfig(const char *filepath) {
    config = toml::parse_file(filepath);
}

ConfigManager::path ConfigManager::getDataDir() const {
    return std::filesystem::path(
        config["io"]["dataDir"].value<std::string>().value());
}

ConfigManager::path ConfigManager::getOutDirSuffix() const {
    return std::filesystem::path(
        config["io"]["outDirSuffix"].value<std::string>().value());
}

double ConfigManager::getSmoothingFactor() {
    return config["transform"]["smoothingFactor"].value<double>().value();
}
