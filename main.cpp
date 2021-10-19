#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "TodoList.h"
#include "ListManager.h"
#include "main.h"
#include "startup.h"

#include "cm.cpp"


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

int main (int argc, char* argv[])
{
    Command Add {"--add", true, 1, 1};
    CommandManager CM{};
    CM.addCommand(Add);
    CM.parse(argc, argv);


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
