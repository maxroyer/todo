#include <iostream>
#include <fstream>
#include <vector>

class todoList
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
};