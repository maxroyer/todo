#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "TodoList.h"
#include "ListManager.h"
#include "main.h"
#include "startup.h"

int main (int argc, char* argv[])
{
    g_running = true;
    std::string configPath = "todo.config";
    SettingsManager SM {configPath};
    ListManager lm {startup(SM)};

    std::vector<std::string> args(0);

    for (int i {1}; i < argc; ++i)
    {
        args.push_back(std::string {argv[i]});
    }

    if (argc > 1)
    {
        query(lm, args);
        SM.saveConfig(lm);
    }
    else if (argc == 1)
    {
        while (g_running)
        {
            query(lm);
        }
    }
    lm.getActiveList().saveToFile();
    SM.saveConfig(lm);
    return 0;
}
