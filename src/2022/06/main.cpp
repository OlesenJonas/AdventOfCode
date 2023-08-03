#include <format>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <string_view>

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

    std::string input;
    getline(inFile, input);

    char inputs[4] = {input[0], input[1], input[2], 0};
    int insertIndex = 3;

    int i;
    for(i = 3; i < input.size(); i++)
    {
        inputs[insertIndex] = input[i];

        if(inputs[0] != inputs[1] && inputs[0] != inputs[2] && inputs[0] != inputs[3] && inputs[1] != inputs[2] &&
           inputs[1] != inputs[3] && inputs[2] != inputs[3])
        {
            break;
        }

        insertIndex = (insertIndex + 1) % 4;
    }

    std::cout << std::format("first marker found after {} characters", i + 1) << std::endl;
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

    std::string input;
    getline(inFile, input);

    // could use two loops and do manual comparison again, but want to try multiset here
    //      turns insert into O(log N) and check for distint into O(N) => O(N + log N)
    //      simple insert and double loop would be O(1) + O(N^2) => O(N^2)
    //      ** although it seems like multiset doesnt offer a direct way to erase just a single key, but concept is
    //      same **
    std::multiset<char> characters;

    auto charactersDistinct = [&]() -> bool
    {
        char lastChar = *characters.begin();
        auto scndIter = ++characters.begin();
        for(auto iter = scndIter; iter != characters.end(); iter++)
        {
            if(*iter == lastChar)
                return false;

            lastChar = *iter;
        }
        return true;
    };

    int i;
    for(i = 0; i < 14; i++)
    {
        characters.insert(input[i]);
    }
    i--;

    if(!charactersDistinct())
    {
        for(i = 14; i < input.size(); i++)
        {
            characters.erase(characters.lower_bound(input[i - 14]));
            characters.insert(input[i]);

            if(charactersDistinct())
            {
                break;
            }
        }
    }

    std::cout << std::format("first marker found after {} characters", i + 1) << std::endl;
}

int main()
{
    task2();
    return 0;
}