#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "TodoList.h"

bool g_running;

class ListManager
{
    TodoList m_activeList; //{"./lists/todo.dat", "todo"};
    std::string m_dir;
    std::vector<std::string> m_fileArr;
    std::vector<std::string> m_titleArr;
    int m_activeIndex;
public:
    ListManager(std::string dir, std::string file, std::string title) : m_dir{dir}, m_activeList{file, title}
    {
        for (const auto& entry : std::filesystem::directory_iterator(dir))
        {
            std::string file{entry.path()};
            std::string title{file.substr(8, file.length())};
            title.erase(title.end()-4, title.end());

            m_fileArr.push_back(file);
            m_titleArr.push_back(title);
        }

        m_activeIndex = 0;
        for (int i{0}; i < m_fileArr.size(); ++i)
        {
            if (m_fileArr[i].find("todo.dat") != std::string::npos)
            {
                m_activeIndex = i;
                break;
            } 
        }

        
    }

    TodoList& getActiveList() {return m_activeList;}
};

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
    ListManager lm{"./lists", dataFile, "todo"};

    while (g_running)
    {
        query(lm.getActiveList());
    }
    
    return 0;
}