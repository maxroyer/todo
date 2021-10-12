#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TodoList.h"

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
        std::cout << "File already exists \n";
    }
}

void query(TodoList& list)
{
    std::cout << "Command: (Add/Remove/View/Exit) ";
    std::string command{};
    std::getline(std::cin, command);

    while (true)
    {
        if (command == "Add" || command == "add")
        {
            list.add();
            break;
        }
        else if (command == "View" || command == "view")
        {
            list.print();
            break;
        }
        else if (command == "quit" || command == "Quit" || command == "Exit" || command == "exit")
        {
            list.saveToFile();
            std::cout << "Exiting\n";
            g_running = false;
            break;
        }
        else if (command == "Remove" || command == "remove")
        {
            list.printNumbered();
            list.removeItem();
            break;
        }
        /*else if (command == "db")
        {
            for (auto i : listtodoArr)
            {
                std::cout << "'" << i << "'" << '\n';
            }
            break;
        }*/
        else
        {
            std::cerr << "Command not recognized!\n";
            break;
        }
    }
}


int main ()
{
    std::string dataFile{"./lists/todo.dat"};
    g_running = true;
    createFile(dataFile);
    TodoList todo{dataFile};

    while (g_running)
    {
        query(todo);
    }
    
    return 0;
}