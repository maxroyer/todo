#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TodoList.h"

TodoList::TodoList(std::string file, std::string title)
{
    name = title;
    setFile(file);
    fileToArr();
}

void TodoList::setFile(std::string file)
{
    filePath = file;
    fileToArr();
}

void TodoList::fileToArr()
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

void TodoList::print() const
{
    std::cout << "\n***************\n***************\n\nTo-Do: "<< name << "\n-------\n";
    for (auto i : todoArr)
    {
        if (i != "") std::cout << "- " << i << '\n';
    }
    std::cout << "\n***************\n***************\n\n";
}

void TodoList::printNumbered() const
{
    int printedNum {1};

    std::cout << "\n**********\n";
    for (int i{0}; i < todoArr.size(); ++i)
    {
        if (todoArr[i] != "") std::cout << '[' << printedNum++ << "] " << todoArr[i] << '\n';
    }
    std::cout << "**********\n";
}

void TodoList::add()
{
    std::cout << "Add to list: ";
    std::string newItem{};
    std::getline(std::cin, newItem);

    todoArr.push_back(newItem);
}

void TodoList::removeItem()
{
    std::cout << "Select number to remove: ";

    int num {};
    std::cin >> num;
    std::cin.clear();
    std::cin.ignore(128, '\n');

    if (num > 0 && num <= todoArr.size()) todoArr[num-1] = "";
}   

void TodoList::saveToFile()
{
    std::ofstream outf{filePath, std::ios::trunc};
    for (std::string item : todoArr)
    {
        if (item != "") outf << item << '\n';
    } 
}