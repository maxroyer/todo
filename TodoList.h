#ifndef TODOLIST_H
#define TODOLIST_H

#include <string>
#include <vector>



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
    void add();
    void removeItem();
    void saveToFile();
    friend class ListManager;
    friend class SettingsManager;

};

#endif