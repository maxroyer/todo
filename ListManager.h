#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include "TodoList.h"

class ListManager
{
    TodoList m_activeList;
    std::string m_dir;
    std::vector<std::string> m_fileArr;
    std::vector<std::string> m_titleArr;
    int m_activeIndex;

    void setActiveList (int index, bool deleteMode = false);
    void purgeArr();

public:
    ListManager(std::string dir, std::string file, std::string title);
    void newList();
    void removeList();
    void printNumbered();
    void selectList(bool deleteMode = false);
    TodoList& getActiveList();
};


#endif