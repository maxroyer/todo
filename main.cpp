#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <limits>
#include "TodoList.h"
#include "ListManager.h"
#include "main.h"

bool g_running;

void createFile (std::string file)
{
    std::ifstream inf {file};

    if (!inf)
    {
        std::cerr << "File not found, creating now..." << '\n';
        std::ofstream outf{file};
    }
    else
    {
        //std::cout << "File already exists \n";
        ;
    }
}

void query(ListManager& lm)
{
    std::cout << "Command(a/r/v/n/s/d/q): ";
    std::string command{};
    std::getline(std::cin, command);
    

    while (true)
    {
        if (command == "Add" || command == "add" || command == "A" || command == "a")
        {
            lm.getActiveList().add();
            //break;
        }
        else if (command == "View" || command == "view" || command == "V" || command == "v")
        {
            lm.getActiveList().print();
            //break;
        }
        else if (command == "quit" || command == "Quit" || command == "Q" || command == "q")
        {
            lm.getActiveList().saveToFile();
            std::cout << "Exiting\n";
            g_running = false;
            //break;
        }
        else if (command == "Remove" || command == "remove" || command == "R" || command == "r")
        {
            lm.getActiveList().printNumbered();
            lm.getActiveList().removeItem();
            //break;
        }
        else if (command == "N" || command == "n")
        {
            lm.newList();
            //break;
        }
        else if (command == "S" || command == "s")
        {
            lm.selectList();
            //break;
        }
        else if (command == "D" || command == "d")
        {
            lm.removeList();
        }
        else
        {
            std::cerr << "Command not recognized!\n";
            //break;
        }
        break;
    }
}


int main ()
{
    std::string dataFile{"./lists/todo.dat"};
    g_running = true;
    createFile(dataFile);

    ListManager lm{"./lists", dataFile, "todo"};
    lm.selectList();
    lm.getActiveList().print();

    while (g_running)
    {
        query(lm);
    }
    
    return 0;
}
