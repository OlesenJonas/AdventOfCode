#include <format>
#include <fstream>
#include <iostream>
#include <string>

/*
    A = Rock = X        = 0
    B = Paper = Y       = 1
    C = Scissors = Z    = 2
*/

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

    unsigned int pointTotal = 0;
    int player1;
    int player2;
    std::string line;
    while(getline(inFile, line))
    {
        player1 = line[0] - 'A';
        player2 = line[2] - 'X';
        int result = (1 + player2 - player1 + 3) % 3;
        pointTotal += result * 3 + (player2 + 1);
    }

    std::cout << std::format("Point total: {}", pointTotal);
}

/*
    X = lose    = 0
    Y = draw    = 1
    Z = win     = 2
*/

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

    unsigned int pointTotal = 0;
    int player1;
    int outcome;
    std::string line;
    while(getline(inFile, line))
    {
        player1 = line[0] - 'A';
        outcome = line[2] - 'X';

        int pointsFromResult = outcome * 3;
        int youChose = (player1 + (outcome - 1) + 3) % 3;

        int pointsFromChoice = youChose + 1;

        pointTotal += pointsFromChoice + pointsFromResult;
    }

    std::cout << std::format("Point total: {}", pointTotal);
}

int main()
{
    task2();
    return 0;
}