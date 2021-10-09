#include <iostream>
#include <fstream>
#include <string>

bool g_running {true};

std::string getItem ()
{
    std::cout << "Add to list: ";
    std::string item{};
    std::getline(std::cin, item);

    return item;
}

void addToFile (std::string file, std::string item)
{
    std::ofstream outf{file, std::ios::app};
    outf << item << '\n';
}

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

void removeItem(std::string file)
{
    ;
}

void printList(std::string file)
{
    std::ifstream inf{file};
    std::cout << "\nTo-Do:\n\n";
    while (inf)
    {
        std::string strIn;
        std::getline(inf, strIn);
        if (strIn != "\0") std::cout << '-' << strIn << '\n';
    }
    std::cout << "\n\n";
}

void exitApp ()
{
    g_running = false;
}

void query(std::string file)
{
    std::cout << "Command: (Add/Remove/View/Exit) ";
    std::string command{};
    std::getline(std::cin, command);

    while (true)
    {
        if (command == "Add" || command == "add")
        {
            addToFile(file, getItem());
            break;
        }
        else if (command == "View" || command == "view")
        {
            printList(file);
            break;
        }
        else if (command == "quit" || command == "Quit" || command == "Exit" || command == "exit")
        {
            g_running = false;
            std::cout << "Exiting\n";
            break;
        }
        else
        {
            std::cerr << "Command not recognized!\n";
            break;
        }
    }
}


int main ()
{
    std::string dataFile{"todo.dat"};
    g_running = true;
    createFile(dataFile);

    while (g_running)
    {
        query(dataFile);
    }


    return 0;
}