#include <bit>
#include <cassert>
#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

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

    int overlaps = 0;

    int start1;
    int end1;
    int start2;
    int end2;

    std::string line;
    while(getline(inFile, line))
    {
        const std::string_view lineView = line;

        auto seperator = line.find_first_of(',');
        std::string_view range1 = lineView.substr(0, seperator);
        std::string_view range2 = lineView.substr(seperator + 1);

        auto dash1 = range1.find_first_of('-');
        auto dash2 = range2.find_first_of('-');

        start1 = atoi(range1.data());
        end1 = atoi(range1.data() + dash1 + 1);

        start2 = atoi(range2.data());
        end2 = atoi(range2.data() + dash2 + 1);

        overlaps += (start1 >= start2 && end1 <= end2) || (start2 >= start1 && end2 <= end1);
    }

    std::cout << std::format("Full overlaps: {}", overlaps);

    inFile.close();
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

    int overlaps = 0;

    int start1;
    int end1;
    int start2;
    int end2;

    std::string line;
    while(getline(inFile, line))
    {
        const std::string_view lineView = line;

        auto seperator = line.find_first_of(',');
        std::string_view range1 = lineView.substr(0, seperator);
        std::string_view range2 = lineView.substr(seperator + 1);

        auto dash1 = range1.find_first_of('-');
        auto dash2 = range2.find_first_of('-');

        start1 = atoi(range1.data());
        end1 = atoi(range1.data() + dash1 + 1);

        start2 = atoi(range2.data());
        end2 = atoi(range2.data() + dash2 + 1);

        overlaps += (start2 <= end1 && start2 >= start1) || (start1 <= end2 && start1 >= start2);
    }

    std::cout << std::format("Full overlaps: {}", overlaps);

    inFile.close();
}

int main()
{
    task2();
    return 0;
}