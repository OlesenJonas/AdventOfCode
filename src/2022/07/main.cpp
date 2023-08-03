#include <cassert>
#include <charconv>
#include <format>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>

void task1()
{
    // const char* filename = SOURCE_PATH "/inputTest.txt";
    const char* filename = SOURCE_PATH "/input.txt";
    std::ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open())
    {
        std::cout << "Couldnt open file " << filename << std::endl;
        exit(-1);
    }

    struct SystemEntry
    {
        // Actually useful here that unordered_map keeps pointers stable, can just directly store parent
        SystemEntry* parent = nullptr;
        std::unordered_map<std::string, SystemEntry> children{};

        int size = 0;

        static SystemEntry Folder(SystemEntry* parent)
        {
            return SystemEntry{.parent = parent};
        }
        static SystemEntry File(SystemEntry* parent, int size)
        {
            return SystemEntry{.parent = parent, .size = size};
        }

        int calcSize()
        {
            int sum = size;
            for(auto& child : children)
            {
                sum += child.second.calcSize();
            }
            size = sum;
            return size;
        }
    };

    std::string line;
    getline(inFile, line); // enters top directory

    SystemEntry rootFolder;
    SystemEntry* currentFolder = &rootFolder;

    getline(inFile, line);

    while(inFile)
    {
        std::string_view lineView = line;
        assert(line[0] == '$');
        if(line.substr(0, 4) == "$ ls")
        {
            // parse ls results
            while(getline(inFile, line) && line[0] != '$')
            {
                lineView = line;
                if(line.substr(0, 3) == "dir")
                {
                    std::string_view dirName = lineView.substr(4);
                    currentFolder->children.emplace(std::string{dirName}, SystemEntry{.parent = currentFolder});
                }
                else
                {
                    auto sepPos = lineView.find_first_of(' ');
                    std::string_view sizeS = lineView.substr(0, sepPos);
                    std::string_view name = lineView.substr(sepPos + 1);
                    int sizeI;
                    auto res = std::from_chars(sizeS.data(), sizeS.data() + sizeS.size(), sizeI);
                    currentFolder->children.emplace(
                        std::string{name}, SystemEntry{.parent = currentFolder, .size = sizeI});
                }
            }
        }
        else if(lineView.substr(2, 2) == "cd")
        {
            // parse directory change
            if(lineView.substr(5, 2) == "..")
            {
                currentFolder = currentFolder->parent;
                getline(inFile, line);
            }
            else
            {
                auto sepPos = lineView.find_last_of(' ');
                std::string_view name = lineView.substr(sepPos + 1);

                // TODO: could use hash equal function to skip string allocation
                auto iter = currentFolder->children.find(std::string{name});
                assert(iter != currentFolder->children.end());
                currentFolder = &iter->second;
                getline(inFile, line);
            }
        }
    }

    rootFolder.calcSize();

    int sum = 0;
    std::stack<SystemEntry*> stack;
    stack.emplace(&rootFolder);

    while(!stack.empty())
    {
        SystemEntry* cur = stack.top();
        stack.pop();

        for(auto& child : cur->children)
        {
            if(!child.second.children.empty()) // ensure that folder
                stack.emplace(&child.second);
        }
        if(cur->size <= 100000)
        {
            sum += cur->size;
        }
    }

    std::cout << std::format("Total is: {}", sum) << std::endl;
}

void task2()
{
    // const char* filename = SOURCE_PATH "/inputTest.txt";
    const char* filename = SOURCE_PATH "/input.txt";
    std::ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open())
    {
        std::cout << "Couldnt open file " << filename << std::endl;
        exit(-1);
    }

    struct SystemEntry
    {
        // Actually useful here that unordered_map keeps pointers stable, can just directly store parent
        SystemEntry* parent = nullptr;
        std::unordered_map<std::string, SystemEntry> children{};

        int size = 0;

        static SystemEntry Folder(SystemEntry* parent)
        {
            return SystemEntry{.parent = parent};
        }
        static SystemEntry File(SystemEntry* parent, int size)
        {
            return SystemEntry{.parent = parent, .size = size};
        }

        int calcSize()
        {
            int sum = size;
            for(auto& child : children)
            {
                sum += child.second.calcSize();
            }
            size = sum;
            return size;
        }
    };

    std::string line;
    getline(inFile, line); // enters top directory

    SystemEntry rootFolder;
    SystemEntry* currentFolder = &rootFolder;

    getline(inFile, line);

    while(inFile)
    {
        std::string_view lineView = line;
        assert(line[0] == '$');
        if(line.substr(0, 4) == "$ ls")
        {
            // parse ls results
            while(getline(inFile, line) && line[0] != '$')
            {
                lineView = line;
                if(line.substr(0, 3) == "dir")
                {
                    std::string_view dirName = lineView.substr(4);
                    currentFolder->children.emplace(std::string{dirName}, SystemEntry{.parent = currentFolder});
                }
                else
                {
                    auto sepPos = lineView.find_first_of(' ');
                    std::string_view sizeS = lineView.substr(0, sepPos);
                    std::string_view name = lineView.substr(sepPos + 1);
                    int sizeI;
                    auto res = std::from_chars(sizeS.data(), sizeS.data() + sizeS.size(), sizeI);
                    currentFolder->children.emplace(
                        std::string{name}, SystemEntry{.parent = currentFolder, .size = sizeI});
                }
            }
        }
        else if(lineView.substr(2, 2) == "cd")
        {
            // parse directory change
            if(lineView.substr(5, 2) == "..")
            {
                currentFolder = currentFolder->parent;
                getline(inFile, line);
            }
            else
            {
                auto sepPos = lineView.find_last_of(' ');
                std::string_view name = lineView.substr(sepPos + 1);

                // TODO: could use hash equal function to skip string allocation
                auto iter = currentFolder->children.find(std::string{name});
                assert(iter != currentFolder->children.end());
                currentFolder = &iter->second;
                getline(inFile, line);
            }
        }
    }

    rootFolder.calcSize();

    int totalSpace = 70000000;
    int needFree = 30000000;
    int currentFree = totalSpace - rootFolder.size;

    SystemEntry* minFolderEnoughSpace = &rootFolder;
    std::stack<SystemEntry*> stack;
    stack.emplace(&rootFolder);

    while(!stack.empty())
    {
        SystemEntry* cur = stack.top();
        stack.pop();

        for(auto& child : cur->children)
        {
            if(!child.second.children.empty()) // ensure that folder
                stack.emplace(&child.second);
        }
        if(currentFree + cur->size >= needFree && cur->size < minFolderEnoughSpace->size)
        {
            minFolderEnoughSpace = cur;
        }
    }

    std::cout << std::format("That folder's size is: {}", minFolderEnoughSpace->size) << std::endl;
}

int main()
{
    task2();
    return 0;
}