#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include "TodoList.h"
#include <string>
#include <vector>

class ListManager
{
    TodoList m_activeList;
    std::string m_dir;
    std::vector<std::string> m_fileArr{};
    std::vector<std::string> m_titleArr{};
    int m_activeIndex;

    void setActiveList (int index, bool deleteMode = false);
    void purgeArr();

public:
    ListManager(std::string dir, std::vector<std::string> fileArr, std::vector<std::string> titleArr, int selectedIndex);
    void createNewList(std::string title);
    void newListFromUser();
    void removeList();
    void printNumbered();
    void selectList(bool deleteMode = false);
    TodoList& getActiveList();

    friend class SettingsManager;
};


#endif