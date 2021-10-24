#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "TodoList.h"
#include "ListManager.h"
#include "main.h"
#include "startup.h"

#include "cm.h"


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
            lm.getActiveList().addFromUser();   
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
            lm.getActiveList().removeItemFromUser(); 
        }
        else if (command == "N" || command == "n")
        {
            lm.newListFromUser();
        }
        else if (command == "S" || command == "s")
        {
            lm.selectListFromUser();
            lm.getActiveList().print();
        }
        else if (command == "D" || command == "d")
        {
            lm.removeListFromUser();
        }
        else
        {
            std::cerr << "Command not recognized!\n"; 
        }
        break;
    }
}



void query(std::vector<Command> commandArr, ListManager& lm)
{
    //  Command input controller with CLI arguments. Takes in std::vector<command> format
    for (auto command : commandArr)
    {
        if (command.getID() == "--add")
        {
            lm.getActiveList().addItem(command.getArg(0));
        }

        else if (command.getID() == "--view")
        {
            lm.getActiveList().print();
        }

        else if (command.getID() == "--done")
        {
            //  need option to enter a number to delete a list item
            if (command.getArgCount() == 0)
            {
                lm.getActiveList().printNumbered();
                lm.getActiveList().removeItemFromUser();
            }
            else if (command.getArgCount() == 1)
            {
                bool argIsNum{ command.getArg(0).find_first_not_of("0123456789") == std::string::npos  };

                if (argIsNum) lm.getActiveList().removeItem(command.getArgAsInt(0) - 1);
                else std::cout << "Invalid Parameters\n";
            }
            else std::cout << "Invalid Parameters\n";
        }

        else if (command.getID() == "--new")
        {
            //  If a list title is included then it is used, otherwise user is promted to enter one
            if (command.getArgCount() == 0) lm.newListFromUser();
            else lm.createNewList(command.getArg(0));

        }

        else if (command.getID() == "--switch")
        {
            bool argIsNum{};
            if (command.getArgCount() == 1)
            {
                bool argIsDigit{ command.getArg(0).find_first_not_of("0123456789") == std::string::npos };

                if (argIsDigit) lm.selectList( command.getArgAsInt(0) - 1 );
                else lm.selectList(command.getArg(0));
            }

            else
            {
                lm.selectListFromUser   ();
                lm.getActiveList().print();
            }

        }

        else if (command.getID() == "--delete")
        {
            if (command.getArgCount() == 1)
            {
                bool argIsDigit{ command.getArg(0).find_first_not_of("0123456789") == std::string::npos };

                if (argIsDigit) lm.removeList(command.getArgAsInt(0));
                else lm.removeList(command.getArg(0));
            }

            else  lm.removeListFromUser();
        }

        else if (command.getID() == "--lists")
        {
            lm.printNumbered();
        }

        else if (command.getID() == "--test")
        {
            std::cout << "test line\n";
        }
    }
}

int main (int argc, char* argv[])
{
    g_running = true;
    std::string configPath = "todo.config";
    SettingsManager SM {configPath};
    ListManager lm {startup(SM)};

    if (argc > 1)
    {
        CommandManager CM{};
        CM.addCommand("--add", true, 1, 1);
        CM.addCommand("--view", false, 0, 0);
        CM.addCommand("--new", true, 1, 1);
        CM.addCommand("--done", false, 1, 0);
        CM.addCommand("--switch", false, 1, 0);
        CM.addCommand("--delete", false, 1, 0);
        CM.addCommand("--lists", false, 0, 0);
        CM.addCommand("--test", false, 0, 0);

        CM.parse(argc, argv);
        query(CM.getExecutables(), lm);
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
