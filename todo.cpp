#include <iostream>
#include <fstream>
#include <vector>

class TodoList
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

    void print()
    {
        std::cout << "\n***************" << "\nTo-Do:\n-------\n";
        for (auto i : todoArr)
        {
            if (i != "") std::cout << "- " << i << '\n';
        }
        std::cout << "***************\n***************\n\n";
    }

    void printNumbered()
    {
        std::cout << "\n**********\n";
        for (int i{0}; i < todoArr.size(); ++i)
        {
            if (todoArr[i] != "") std::cout << '[' << i + 1 << "] " << todoArr[i] << '\n';
        }
        std::cout << "**********\n";
    }

    void add ()
    {
        std::cout << "Add to list: ";
        std::string newItem{};
        std::getline(std::cin, newItem);

        todoArr.push_back(newItem);
    }

    void removeItem()
    {
        std::cout << "Select number to remove: ";

        int num {};
        std::cin >> num;
        std::cin.clear();
        std::cin.ignore(128, '\n');

        if (num > 0 && num <= todoArr.size()) todoArr[num-1] = "";
    }   

    void saveToFile()
    {
        std::ofstream outf{filePath, std::ios::trunc};
        for (std::string item : todoArr)
        {
            if (item != "") outf << item << '\n';
        } 
    }

};

int main()
{
    TodoList list{};
    list.setFile("todo.dat");
    list.fileToArr();
    list.print();
    list.add();
    list.print();
    list.printNumbered();
    list.removeItem();
    list.print();




    return 0;
}
