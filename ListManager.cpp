#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <limits>
#include "ListManager.h"
#include "TodoList.h"


ListManager::ListManager (std::string dir, std::vector<std::string> fileArr, std::vector<std::string> titleArr, int selectedIndex)
    : m_dir {dir}, m_fileArr {fileArr}, m_titleArr {titleArr}, m_activeList {fileArr[selectedIndex], titleArr[selectedIndex]}, m_activeIndex {selectedIndex}
{
    //  ListManager Constructor, requires dir string, a vector of strings containing file paths,
    //  a corresponding vector of titles, and the user selected index for the active list
    purgeArr();
    m_activeList.print();
}

void ListManager::newList()
{
    //  Gets user input to name and create a new list
    std::cout << "New List Name: ";
    std::string title;
    std::getline(std::cin >> std::ws, title);
    std::string path {m_dir + '/' + title + ".dat"};

    m_fileArr.push_back(path);
    m_titleArr.push_back(title);
    setActiveList(m_fileArr.size() - 1);
}

void ListManager::removeList()
{
    //  Calls printNumbered(), the gets user input to delete a list
    printNumbered();
    int num {0};

    while(true)
    {
        std::cout << "Select a list to delete: ";
        std::cin >> num;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Item not found\n";
            continue;
        }
        std::cin.clear();
        std::cin.ignore(128, '\n');
    
        if (num < 1 || num > m_titleArr.size())
        {
            std::cout << "Out of Range\n";
            continue;
        }
        else break;
    }

    int remove{num-1};

    std::ifstream inf{m_fileArr[remove]};
    inf.close();
    std::filesystem::remove(m_fileArr[remove]);

    m_fileArr[remove] = "";
    m_titleArr[remove] = "";
    purgeArr();

    if (m_fileArr.size() != 0 && remove == m_activeIndex) selectList(true);
    else if (m_fileArr.size() == 0)
    {
        m_fileArr.push_back(createFile());
        m_activeIndex = 0;
        m_titleArr.push_back(pathToTitle(m_fileArr[0]));
        m_activeList = TodoList{m_fileArr[m_activeIndex], m_titleArr[m_activeIndex]};
    }
    else selectList();

}

void ListManager::printNumbered()
{
    // Prints numbered list of ListManager.m_titleArr
    int printedNum {1};
    std::cout << "\n**********\n";
    for (int i{0}; i < m_titleArr.size(); ++i)
    {
        if (m_titleArr[i] != "") std::cout << '[' << printedNum++ << ']' << ' ' << m_titleArr[i] << '\n';
    }
    std::cout << "**********\n\n";

}

void ListManager::selectList(bool deleteMode)
{
    // Calls printNumbered(), then gets user input to select a new active list
    // Parameter deleteMode = false by default, use true when calling after deleting a list
    printNumbered();
    int num {0};

    while(num < 1 || num > m_titleArr.size())
    {
        std::cout << "Select a list to open: ";
        std::cin >> num;
        std::cin.clear();
        std::cin.ignore(128, '\n');
    }

    if (deleteMode)
    {
        setActiveList(num - 1, deleteMode);
        m_activeList.print(); 
    }
    else
    {
        setActiveList(num - 1);
        m_activeList.print();
    }
}

void ListManager::setActiveList (int index, bool deleteMode)
{
    //  Takes index which is selected index in ListManager.m_fileArr and uses it to set ListManager.m_activeTodoList.
    //  Optional parameter deleteMode (default false) determines if the current TodoList is saved first.
    if (!deleteMode) m_activeList.saveToFile();
    m_activeIndex = index;
    m_activeList = TodoList{m_fileArr[m_activeIndex], m_titleArr[m_activeIndex]};
}

void ListManager::purgeArr()
{
    //  Removes elements equal to "" from m_titleArr and m_fileArr
    for (int i{0}; i < m_fileArr.size(); ++i)
    {
        if (m_fileArr[i] == "")
        {
            m_fileArr.erase(m_fileArr.begin() + i);
            m_titleArr.erase(m_titleArr.begin() + i);
        }
    }
}

TodoList& ListManager::getActiveList()
{
    return m_activeList;
}