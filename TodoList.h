#ifndef TODOLIST_H
#define TODOLIST_H

class TodoList
{
    std::vector<std::string> todoArr{};
    std::string filePath;
    std::string name;

public:
    TodoList(std::string file, std::string title);

    void setFile(std::string file);
    void fileToArr();
    void print() const;
    void printNumbered() const;
    void add();
    void removeItem();
    void saveToFile();
    friend class ListManager;

};

#endif