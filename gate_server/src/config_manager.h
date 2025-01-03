#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <unordered_map>

struct SectionInfo
{
  SectionInfo() = default;
  ~SectionInfo() = default;

  std::string operator[](const std::string& key)
  {
    if (m_sectionDatas.find(key) == m_sectionDatas.end())
      return "";
    return m_sectionDatas[key];
  }

  std::unordered_map<std::string, std::string> m_sectionDatas;
};

class ConfigManager
{
public:
  ConfigManager();

  SectionInfo operator[](const std::string& sectionName);

private:
  std::unordered_map<std::string, SectionInfo> m_mapConfig;
};

#endif // CONFIGMANAGER_H
