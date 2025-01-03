#include "config_manager.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fmt/format.h>

#include <filesystem>

ConfigManager::ConfigManager()
{
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::filesystem::path configPath = currentPath / "config.ini";
  fmt::println("config path: {}", configPath.string());

  boost::property_tree::ptree pt;
  boost::property_tree::read_ini(configPath.string(), pt);

  for (const auto& section : pt) {
    const auto& sectionName = section.first;
    const auto& sectionTree = section.second;
    SectionInfo sectionInfo;
    for (const auto& item : sectionTree) {
      const std::string& key = item.first;
      const std::string& value = item.second.get_value<std::string>();
      sectionInfo.m_sectionDatas.emplace(key, value);
    }

    m_mapConfig.emplace(sectionName, sectionInfo);
  }

  for (const auto& section : m_mapConfig) {
    fmt::println("section: {}", section.first);
    for (const auto& item : section.second.m_sectionDatas) {
      fmt::println("  {}: {}", item.first, item.second);
    }
  }
}

SectionInfo
ConfigManager::operator[](const std::string& sectionName)
{
  if (m_mapConfig.find(sectionName) == m_mapConfig.end())
    return SectionInfo();
  return m_mapConfig[sectionName];
}

ConfigManager&
ConfigManager::getInstance()
{
  static ConfigManager instance;
  return instance;
}
