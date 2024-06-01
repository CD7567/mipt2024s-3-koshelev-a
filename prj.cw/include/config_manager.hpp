#ifndef MIPT2024S_3_KOSHELEV_A_CONFIG_MANAGER_HPP
#define MIPT2024S_3_KOSHELEV_A_CONFIG_MANAGER_HPP

#include <filesystem>
#include <toml++/toml.hpp>

namespace cw {

class ConfigManager {
  private:
    using path = std::filesystem::path;

    ConfigManager() = default;
    ConfigManager(const ConfigManager&) = default;
    ConfigManager& operator=(const ConfigManager&) = delete;

    toml::table config;

  public:
    static ConfigManager& getInstance();

    void setConfig(const char* filepath);

    path getDataDir() const;
    path getOutDirSuffix() const;
    path getGenDirSuffix() const;

    double getSmoothingFactor() const;

    double getGenStep() const;
    double getGenFOV() const;
    double getGenInitialBound() const;
};

}  // namespace cw

#endif  // MIPT2024S_3_KOSHELEV_A_CONFIG_MANAGER_HPP
