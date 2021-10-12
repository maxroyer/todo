#ifndef TODOLIST_H
#define TODOLIST_H

class TodoList
{
    std::vector<std::string> todoArr{};
    std::string filePath;

public:
    TodoList(std::string file);

    void setFile(std::string file);
    void fileToArr();
    void print() const;
    void printNumbered() const;
    void add();
    void removeItem();
    void saveToFile();

};

#endif