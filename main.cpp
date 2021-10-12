#include <iostream>
#include <fstream>
#include <string>
#include <vector>


bool g_running;
using todo_t = std::vector<std::string>;

class TodoList
{
    std::vector<std::string> todoArr{};
    std::string filePath{};

public:
    void setFile(std::string file)
    {
        filePath = file;
    }

    void fileToArr()
    {
        std::ifstream inf{filePath};
        int listLength {};
        std::string temp;
        while (inf)
        {
            std::getline(inf, temp);
            ++listLength;
        }

        todoArr.resize(listLength);
        inf.close();
        inf.open(filePath);

        int counter {0};
        while (inf && counter < listLength - 1)
        {
            std::getline(inf, temp);
            todoArr[counter] = temp;
            ++counter;
        }
    }

    void print()
    {
        std::cout << "\n***************" << "\nTo-Do:\n-------\n";
        for (auto i : todoArr)
        {
            if (i != "") std::cout << "- " << i << '\n';
        }
        std::cout << "***************\n***************\n\n";
    }

    void printNumbered()
    {
        int printedNum {1};

        std::cout << "\n**********\n";
        for (int i{0}; i < todoArr.size(); ++i)
        {
            if (todoArr[i] != "") std::cout << '[' << printedNum++ << "] " << todoArr[i] << '\n';
        }
        std::cout << "**********\n";
    }

    void add()
    {
        std::cout << "Add to list: ";
        std::string newItem{};
        std::getline(std::cin, newItem);

        todoArr.push_back(newItem);
    }

    void removeItem()
    {
        std::cout << "Select number to remove: ";

        int num {};
        std::cin >> num;
        std::cin.clear();
        std::cin.ignore(128, '\n');

        if (num > 0 && num <= todoArr.size()) todoArr[num-1] = "";
    }   

    void saveToFile()
    {
        std::ofstream outf{filePath, std::ios::trunc};
        for (std::string item : todoArr)
        {
            if (item != "") outf << item << '\n';
        } 
    }

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

void query(TodoList list)
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
    std::string dataFile{"todo.dat"};
    g_running = true;
    createFile(dataFile);
    TodoList todo{};
    todo.setFile(dataFile);
    todo.fileToArr();

    while (g_running)
    {
        query(todo);
    }
    
    return 0;
}