#ifndef TODOLIST_H
#define TODOLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

class TodoList
{
    std::vector<std::string> todoArr{};
    std::string filePath;
    std::string name;

public:
    TodoList(std::string file, std::string title);
    
    void setFile(std::string file);
    void fileToArr();
    void purgeArr();
    void print() const;
    void printNumbered();
    void addFromUser();
    void addItem(std::string item);
    void removeItemFromUser ();
    void removeItem(int index);
    void saveToFile();
    friend class ListManager;
    friend class SettingsManager;
};

#endif