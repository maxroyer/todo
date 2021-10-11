#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>


bool g_running;
using todo_t = std::vector<std::string>;

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

void fileToArr(std::string file, todo_t& todoArr)
{
    std::ifstream inf{file};
    int listLength {};
    std::string temp;
    while (inf)
    {
        std::getline(inf, temp);
        ++listLength;
    }

    todoArr.resize(listLength);
    inf.close();
    inf.open(file);

    int counter {0};
    while (inf && counter < listLength - 1)
    {
        std::getline(inf, temp);
        todoArr[counter] = temp;
        ++counter;
    }
}

std::string getItem ()
{
    std::cout << "Add to list: ";
    std::string item{};
    std::getline(std::cin, item);

    return item;
}

void addToArr (todo_t& todoArr)
{
    std::cout << "Add to list: ";
    std::string newItem{};
    std::getline(std::cin, newItem);

    int listlength {static_cast<int>(todoArr.size())};
    todoArr.resize(listlength+1);
    todoArr[listlength] = todoArr[listlength-1];
    todoArr[listlength-1] = newItem;
}

void removeItem(todo_t& todoArr)
{
    std::cout << "Select number to remove: ";

    int num {};
    std::cin >> num;
    std::cin.clear();
    std::cin.ignore(128, '\n');

    if (num > 0 && num <= todoArr.size()) todoArr[num-1] = "0";
}

void printList(const todo_t todoArr)
{
    std::cout << "\n**********" << "\nTo-Do:\n-------\n";
    for (auto i : todoArr)
    {
        if (i != "" && i != "0") std::cout << "- " << i << '\n';
    }
    std::cout << "**********" << "\n\n";
}

void printListNumbered(const todo_t todoArr)
{
    std::cout << "\n**********\n";
    for (int i{0}; i < todoArr.size(); ++i)
    {
        if (todoArr[i] != "0" && todoArr[i] != "") std::cout << '[' << i + 1 << "] " << todoArr[i] << '\n';
    }
    std::cout << "**********\n";
}

void saveFileAndExit (std::string file, todo_t todoArr)
{
    std::ofstream outf{file, std::ios::trunc};
    for (std::string item : todoArr)
    {
        if (item != "" && item != "0") outf << item << '\n';
    }
    g_running = false;
}

void query(std::string file, todo_t& todoArr)
{
    std::cout << "Command: (Add/Remove/View/Exit) ";
    std::string command{};
    std::getline(std::cin, command);

    while (true)
    {
        if (command == "Add" || command == "add")
        {
            addToArr(todoArr);
            break;
        }
        else if (command == "View" || command == "view")
        {
            printList(todoArr);
            break;
        }
        else if (command == "quit" || command == "Quit" || command == "Exit" || command == "exit")
        {
            saveFileAndExit(file, todoArr);
            std::cout << "Exiting\n";
            break;
        }
        else if (command == "Remove" || command == "remove")
        {
            printListNumbered(todoArr);
            removeItem(todoArr);
            break;
        }
        else if (command == "db")
        {
            for (auto i : todoArr)
            {
                std::cout << "'" << i << "'" << '\n';
            }
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
    todo_t list{};
    fileToArr(dataFile, list);

    while (g_running)
    {
        query(dataFile, list);
    }
    
    return 0;
}