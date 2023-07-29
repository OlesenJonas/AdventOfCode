#include <bit>
#include <cassert>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

inline uint32_t getIndex(const char& c)
{
    if(c >= 'a')
        return (c - 'a');
    return (c - 'A') + 26;
}

void task1()
{
    const char* filename = SOURCE_PATH "/input.txt";
    // const char* filename = SOURCE_PATH "/inputTest.txt";
    std::ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open())
    {
        std::cout << "Couldnt open file " << filename << std::endl;
        exit(-1);
    }

    // if it doesnt matter how often something is duplicated we can just use a bitmask
    uint64_t items1 = 0u;
    uint64_t items2 = 0u;
    uint64_t both = 0u;
    uint32_t sum = 0;

    std::string line;
    while(getline(inFile, line))
    {
        const std::string_view lineView = line;
        std::string_view comp1 = lineView.substr(0, lineView.size() / 2);
        std::string_view comp2 = lineView.substr(lineView.size() / 2);

        items1 = 0u;
        items2 = 0u;

        for(const auto& c : comp1)
        {
            items1 |= 1ull << getIndex(c);
        }
        for(const auto& c : comp2)
        {
            items2 |= 1ull << getIndex(c);
        }

        both = items1 & items2;

        while(both > 0)
        {
            int indexSet = std::countr_zero(both);
            both ^= 1ull << indexSet;

            sum += indexSet + 1;
        }
    }

    std::cout << std::format("Priority sum: {}", sum);
}

void task2()
{
    const char* filename = SOURCE_PATH "/input.txt";
    // const char* filename = SOURCE_PATH "/inputTest.txt";
    std::ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open())
    {
        std::cout << "Couldnt open file " << filename << std::endl;
        exit(-1);
    }

    uint64_t items[3] = {0u, 0u, 0u};
    uint64_t all = 0u;

    uint8_t inGroupIndex = 0;
    uint32_t sum = 0;

    std::string line;
    while(getline(inFile, line))
    {
        for(const auto& c : line)
        {
            items[inGroupIndex] |= 1ull << getIndex(c);
        }

        if(inGroupIndex == 2)
        {
            all = items[0] & items[1] & items[2];
            assert(std::popcount(all) == 1);

            sum += std::countr_zero(all) + 1;

            items[0] = 0u;
            items[1] = 0u;
            items[2] = 0u;
        }

        inGroupIndex = (inGroupIndex + 1) % 3u;
    }

    std::cout << std::format("Priority sum: {}", sum);
}

int main()
{
    task2();
    return 0;
}