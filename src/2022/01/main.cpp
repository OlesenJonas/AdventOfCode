#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

/*
    Also stores elf indices, which isnt actually required
*/

void task1()
{
    const char* filename = SOURCE_PATH "/input.txt";
    std::ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open())
    {
        std::cout << "Couldnt open file " << filename << std::endl;
        exit(-1);
    }

    int currentElfIndex = 0;
    int currentElfCalories = 0;
    int maxElfIndex = 0;
    int maxElfCalories = 0;
    std::string line;
    while(getline(inFile, line))
    {
        if(line.empty())
        {
            if(currentElfCalories > maxElfCalories)
            {
                maxElfCalories = currentElfCalories;
                maxElfIndex = currentElfIndex;
            }
            currentElfIndex++;
            currentElfCalories = 0;
            continue;
        }

        currentElfCalories += std::atoi(line.c_str());
    }
    // last elf
    {
        if(currentElfCalories > maxElfCalories)
        {
            maxElfCalories = currentElfCalories;
            maxElfIndex = currentElfIndex;
        }
        currentElfIndex++;
        currentElfCalories = 0;
    }

    std::cout << std::format("The most calories are carried by Elf {}: {}", maxElfIndex + 1, maxElfCalories)
              << std::endl;
}

struct ElfData
{
    int index = 0;
    int calories = 0;
};
void insertElf(ElfData (&elves)[3], int index, int calories)
{
    int insertIndex = 3;
    for(int i = 3; i > 0; i--)
    {
        if(calories < elves[i - 1].calories)
        {
            break;
        }
        insertIndex = i - 1;
    }

    if(insertIndex < 3)
    {
        for(int i = 2; i > insertIndex; i--)
        {
            elves[i] = elves[i - 1];
        }
        elves[insertIndex] = {
            .index = index, //
            .calories = calories,
        };
    }
}

void task2()
{
    const char* filename = SOURCE_PATH "/input.txt";
    std::ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open())
    {
        std::cout << "Couldnt open file " << filename << std::endl;
        exit(-1);
    }

    ElfData topElves[3];

    int currentElfIndex = 0;
    int currentElfCalories = 0;
    std::string line;
    while(getline(inFile, line))
    {
        if(!line.empty())
        {
            currentElfCalories += std::atoi(line.c_str());
            continue;
        }

        insertElf(topElves, currentElfIndex, currentElfCalories);

        currentElfIndex++;
        currentElfCalories = 0;
    }
    insertElf(topElves, currentElfIndex, currentElfCalories);

    std::cout << std::format(
                     "The most calories are carried by Elves {}, {} & {}: {}",
                     topElves[0].index + 1,
                     topElves[1].index + 1,
                     topElves[2].index + 1,
                     topElves[0].calories + topElves[1].calories + topElves[2].calories)
              << std::endl;
}

int main()
{
    task2();
    return 0;
}