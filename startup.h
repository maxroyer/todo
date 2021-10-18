#ifndef STARTUP_H
#define STARTUP_H

#include <string>
#include <vector>

class ListManager;

class SettingsManager
{
    std::string m_listDir{};
    std::string m_configPath;
    std::string m_activeTodoPath{};
public:
    SettingsManager (std::string configPath);
    bool checkConfig ();
    void createConfigFile ();
    void loadConfig ();
    void saveConfig (ListManager& lm);
    std::string getListDir ();
    std::string getActiveListPath();
};

void createFile (std::string file);
std::string createFile ();
std::string pathToTitle(std::string path);
ListManager startup (std::string dir);
ListManager startup (SettingsManager& SM);

#endif