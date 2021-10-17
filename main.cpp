#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "TodoList.h"
#include "ListManager.h"
#include "main.h"

bool g_running;

class SettingsManager
{
    std::string m_listDir;
    std::string m_configPath;
    std::string m_activeTodoPath;

public:
    SettingsManager (std::string configPath) : m_configPath {configPath}
    {
        bool configExist {checkConfig()};

        if (configExist) loadConfig();
        else
        {
            createConfigFile();
            std::cout << "Config not found, creating now...\nUsing default path for lists folder.\n";
            m_listDir = "./lists";
            m_activeTodoPath = "";
        }
    }

    bool checkConfig () 
    {
        if (std::filesystem::exists(m_configPath)) return true;
        else return false;
    }

    void createConfigFile () 
    {
        //  Creates new or deletes and replaces current config file
        std::ofstream outf{m_configPath, std::ios::trunc};
    }

    void loadConfig ()
    {
        std::ifstream inf{m_configPath};
        std::vector<std::string> settingsArr (0);
        std::string temp{};
        while (inf)
        {
            std::getline(inf, temp);
            settingsArr.push_back(temp);
        }
        m_listDir = settingsArr[0];
        m_activeTodoPath = settingsArr[1];
    }

    void saveConfig (ListManager& lm)
    {
        //  Should probably take a ListManager as a parameter.
        m_activeTodoPath = lm.m_activeList.filePath;
        std::ofstream outf {m_configPath, std::ios::trunc};
        
        outf << m_listDir << '\n' << m_activeTodoPath;
    }

    std::string getListDir ()
    {
        return m_listDir;
    }

    std::string getActiveListPath()
    {
        return m_activeTodoPath;
    }
};

void createFile (std::string file)
{
    //  Create file with passed name, not currently used anywhere
    std::ifstream inf {file};

    if (!inf)
    {
        std::cerr << "File not found, creating now..." << '\n';
        std::ofstream outf{file};
    }
    else
    {
        //std::cout << "File already exists \n";
    }
}

std::string createFile ()
{
    //  Ask user to enter a name to create a file, for when no files exists,
    //  and returns the file path
    std::cout << "You don't have any lists, create one now: ";
    std::string title;
    std::getline(std::cin >> std::ws, title);
    std::string path {"./lists/" + title + ".dat"};
    std::ofstream outf{path};
    return path;
}

std::string pathToTitle (std::string path)
{
    //  Takes an file path input, in form "./path/to/file.dat", returns "file"
    std::string title;
    std::string::size_type pathEnd;

    pathEnd = path.find_last_of('/');
    title = path.substr(pathEnd+1);
    title.erase(title.end()-4, title.end());

    return title;
}

void query(ListManager& lm)
{
    //  Command input controller
    std::cout << "Command(a/r/v/n/s/d/q): ";
    std::string command{};
    std::getline(std::cin, command);
    

    while (true)
    {
        if (command == "Add" || command == "add" || command == "A" || command == "a")
        {
            lm.getActiveList().add();   
        }
        else if (command == "View" || command == "view" || command == "V" || command == "v")
        {
            lm.getActiveList().print();
        }
        else if (command == "quit" || command == "Quit" || command == "Q" || command == "q")
        {
            lm.getActiveList().saveToFile();
            std::cout << "Exiting\n";
            g_running = false;
        }
        else if (command == "Remove" || command == "remove" || command == "R" || command == "r")
        {
            lm.getActiveList().printNumbered();
            lm.getActiveList().removeItem(); 
        }
        else if (command == "N" || command == "n")
        {
            lm.newList();
        }
        else if (command == "S" || command == "s")
        {
            lm.selectList();
        }
        else if (command == "D" || command == "d")
        {
            lm.removeList();
        }
        else
        {
            std::cerr << "Command not recognized!\n"; 
        }
        break;
    }
}

void query(ListManager& lm, std::vector<std::string> argv)
{
    //  Command input controller with CLI arguments. Takes in std::vector format
    int argc {static_cast<int>(argv.size())};
    for (int i{0}; i < argc; ++i)
    {
        if (argv[i] == "--add")
        {
            lm.getActiveList().add();
        }
        else if (argv[i] == "--todo")
        {
            lm.getActiveList().print();
        }
        else if (argv[i] == "--done")
        {
            lm.getActiveList().printNumbered();
            lm.getActiveList().removeItem();
        }
        else if (argv[i] == "--new")
        {
            lm.newList();;
        }
        else if (argv[i] == "--switch")
        {
            lm.selectList();;
        }
        else if (argv[i] == "--delete")
        {
            lm.removeList();;
        }
        else if (argv[i] == "--lists")
        {
            lm.printNumbered();
        }
    }
}

ListManager startup (std::string dir)
{
    //  Looks through given folder, returns a ListManager
    std::vector<std::string> fileArr (0);
    std::vector<std::string> titleArr (0);

    for (const auto& entry : std::filesystem::directory_iterator(dir))
    {
        std::string file{entry.path()};
        std::string title {pathToTitle(file)};

        fileArr.push_back(file);
        titleArr.push_back(title);
    }

    if (!fileArr.empty())
    {
        
        int printedNum {1};

        std::cout << "\n**********\n";
        for (int i{0}; i < titleArr.size(); ++i)
        {
            if (titleArr[i] != "") std::cout << '[' << printedNum++ << ']' << ' ' << titleArr[i] << '\n';
        }
        std::cout << "**********\n\n";

        int num {0};
        while(num < 1 || num > titleArr.size())
        {
            std::cout << "Select a list to open: ";
            std::cin >> num;
            std::cin.clear();
            std::cin.ignore(128, '\n');
        }

        return ListManager {dir, fileArr, titleArr, num-1};
    }
    else
    {
        std::string filePath = createFile();
        std::string title {pathToTitle(filePath)};

        fileArr.push_back(filePath);
        titleArr.push_back(title);
        
        return ListManager {dir, fileArr, titleArr, 0};
    }
}

ListManager startup (SettingsManager& SM)
{
    //  Looks through given folder, returns a ListManager
    std::string dir {SM.getListDir()};
    std::vector<std::string> fileArr (0);
    std::vector<std::string> titleArr (0);

    for (const auto& entry : std::filesystem::directory_iterator(dir))
    {
        std::string file{entry.path()};
        std::string title {pathToTitle(file)};

        fileArr.push_back(file);
        titleArr.push_back(title);
    }

    bool preselected = {SM.getActiveListPath() != ""};

    if (!fileArr.empty() && preselected)
    {
        std::string activePath = SM.getActiveListPath();
        int activeIndex {};
        for (int ii{0}; ii < fileArr.size(); ++ii )
        {
            if (fileArr[ii] == activePath)
            {
                activeIndex = ii;
            }
        }

        return ListManager {dir, fileArr, titleArr, activeIndex};
    }
    else if (!fileArr.empty() && !preselected)
    {
        int printedNum {1};

        std::cout << "\n**********\n";
        for (int i{0}; i < titleArr.size(); ++i)
        {
            if (titleArr[i] != "") std::cout << '[' << printedNum++ << ']' << ' ' << titleArr[i] << '\n';
        }
        std::cout << "**********\n\n";

        int num {0};
        while(num < 1 || num > titleArr.size())
        {
            std::cout << "Select a list to open: ";
            std::cin >> num;
            std::cin.clear();
            std::cin.ignore(128, '\n');
        }

        return ListManager {dir, fileArr, titleArr, num-1};
    }
    else
    {
        std::string filePath = createFile();
        std::string title {pathToTitle(filePath)};

        fileArr.push_back(filePath);
        titleArr.push_back(title);
        
        return ListManager {dir, fileArr, titleArr, 0};
    }
}

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

    SM.saveConfig(lm);
    return 0;
}
