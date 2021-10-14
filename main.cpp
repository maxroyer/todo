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
    //  Create file with passed name, 
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

std::string createFile ()
{
    //  Ask user to enter a name to create a file, for when no files exists,
    //  and returns the file path
    std::cout << "You don't have any lists, create one now: ";
    std::string title;
    std::getline(std::cin >> std::ws, title);
    std::string path {"lists/" + title + ".dat"};
    std::ofstream outf{path};
    return path;
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

/*
int main ()
{
    std::string dataFile{"./lists/todo.dat"};
    g_running = true;
    createFile(dataFile);
    ListManager lm{};
    //ListManager lm{dataFile, "todo"};
    //lm.selectList();

    while (g_running)
    {
        query(lm);
    }
    
    return 0;
}*/

ListManager startup (std::string dir)
{
    //  Looks through given folder, returns a ListManager
    std::vector<std::string> fileArr (0);
    std::vector<std::string> titleArr (0);

    for (const auto& entry : std::filesystem::directory_iterator(dir))
    {
        std::string file{entry.path()};
        std::string title{file.substr(6, file.length())};
        title.erase(title.end()-4, title.end());

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
        std::string title{filePath.substr(6, filePath.length())};
        title.erase(title.end()-4, title.end());

        fileArr.push_back(filePath);
        titleArr.push_back(title);
        
        return ListManager {dir, fileArr, titleArr, 0};
    }
}

int main ()
{
    g_running = true;
    std::string listDir = "lists/";
    ListManager lm {startup(listDir)};

    while(g_running)
    {
        query(lm);
    }

    return 0;
}
