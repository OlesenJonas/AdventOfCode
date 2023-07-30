#include <cassert>
#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void task1()
{
    const char* filename = SOURCE_PATH "/input.txt";
    // const char* filename = SOURCE_PATH "/inputTest.txt";
    std::ifstream inFile(filename, std::ios_base::in | std::ios_base::binary);
    if(!inFile.is_open())
    {
        std::cout << "Couldnt open file " << filename << std::endl;
        exit(-1);
    }

    int maxInitialStackHeight = 0;
    std::string line = "[";
    std::vector<std::streampos> stackLineStarts;
    while(line.find_first_of('[') != std::string::npos)
    {
        stackLineStarts.push_back(inFile.tellg());
        getline(inFile, line);
        maxInitialStackHeight++;
    }
    stackLineStarts.pop_back();
    // assume just one digit stack numbers, otherwise
    // everything would be a lot uglier
    // -3 since file is openeded in binary mode so additional \r could be there
    int stackCount = atoi(&line[line.size() - 3]);

    // using vectors here since theyre contiguous unlike dequeue
    // and all the "stack" ops needed are trivial to do the vectors here
    std::vector<std::vector<char>> stacks{static_cast<uint32_t>(stackCount)};
    for(auto& stack : stacks)
    {
        stack.reserve(maxInitialStackHeight);
    }

    for(int i = stackLineStarts.size() - 1; i >= 0; i--)
    {
        inFile.seekg(stackLineStarts[i], std::ios_base::beg);
        getline(inFile, line);

        const std::string_view lineView = line;
        auto foundPos = lineView.find('[', 0);
        while(foundPos < std::string::npos)
        {
            int stackIndex = foundPos / 4;
            stacks[stackIndex].push_back(lineView[foundPos + 1]);
            foundPos = lineView.find('[', foundPos + 1);
        }
    }
    inFile.seekg(stackLineStarts[stackLineStarts.size() - 1], std::ios_base::beg);

    // skip lines to start of moves
    getline(inFile, line);
    getline(inFile, line);
    getline(inFile, line);

    int amount = -1;
    int start = -1;
    int end = -1;

    // parse moves;
    while(getline(inFile, line))
    {
        std::from_chars_result res;
        const char* fst = line.data() + 5;
        const char* lst = &line[line.size()];

        res = std::from_chars(fst, lst, amount);
        fst = res.ptr + 6;

        res = std::from_chars(fst, lst, start);
        fst = res.ptr + 4;

        res = std::from_chars(fst, lst, end);

        auto& from = stacks[start - 1];
        auto& to = stacks[end - 1];
        // insert into new stack
        to.insert(to.end(), from.rbegin(), std::next(from.rbegin(), amount));
        // remove from old stack
        from.resize(from.size() - amount);
    }

    for(const auto& stack : stacks)
    {
        std::cout << stack[stack.size() - 1];
    }
    std::cout << std::endl;

    inFile.close();
}

void task2()
{
    const char* filename = SOURCE_PATH "/input.txt";
    // const char* filename = SOURCE_PATH "/inputTest.txt";
    std::ifstream inFile(filename, std::ios_base::in | std::ios_base::binary);
    if(!inFile.is_open())
    {
        std::cout << "Couldnt open file " << filename << std::endl;
        exit(-1);
    }

    int maxInitialStackHeight = 0;
    std::string line = "[";
    std::vector<std::streampos> stackLineStarts;
    while(line.find_first_of('[') != std::string::npos)
    {
        stackLineStarts.push_back(inFile.tellg());
        getline(inFile, line);
        maxInitialStackHeight++;
    }
    stackLineStarts.pop_back();
    // assume just one digit stack numbers, otherwise
    // everything would be a lot uglier
    // -3 since file is openeded in binary mode so additional \r could be there
    int stackCount = atoi(&line[line.size() - 3]);

    // using vectors here since theyre contiguous unlike dequeue
    // and all the "stack" ops needed are trivial to do the vectors here
    std::vector<std::vector<char>> stacks{static_cast<uint32_t>(stackCount)};
    for(auto& stack : stacks)
    {
        stack.reserve(maxInitialStackHeight);
    }

    for(int i = stackLineStarts.size() - 1; i >= 0; i--)
    {
        inFile.seekg(stackLineStarts[i], std::ios_base::beg);
        getline(inFile, line);

        const std::string_view lineView = line;
        auto foundPos = lineView.find('[', 0);
        while(foundPos < std::string::npos)
        {
            int stackIndex = foundPos / 4;
            stacks[stackIndex].push_back(lineView[foundPos + 1]);
            foundPos = lineView.find('[', foundPos + 1);
        }
    }
    inFile.seekg(stackLineStarts[stackLineStarts.size() - 1], std::ios_base::beg);

    // skip lines to start of moves
    getline(inFile, line);
    getline(inFile, line);
    getline(inFile, line);

    int amount = -1;
    int start = -1;
    int end = -1;

    // parse moves;
    while(getline(inFile, line))
    {
        std::from_chars_result res;
        const char* fst = line.data() + 5;
        const char* lst = &line[line.size()];

        res = std::from_chars(fst, lst, amount);
        fst = res.ptr + 6;

        res = std::from_chars(fst, lst, start);
        fst = res.ptr + 4;

        res = std::from_chars(fst, lst, end);

        auto& from = stacks[start - 1];
        auto& to = stacks[end - 1];
        // insert into new stack
        //      part2 is trivial using a vector
        to.insert(to.end(), std::prev(from.end(), amount), from.end());
        // remove from old stack
        from.resize(from.size() - amount);
    }

    for(const auto& stack : stacks)
    {
        std::cout << stack[stack.size() - 1];
    }
    std::cout << std::endl;

    inFile.close();
}

int main()
{
    task2();
    return 0;
}