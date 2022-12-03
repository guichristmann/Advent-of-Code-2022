#include <fstream>
#include <iostream>
#include <string>

int32_t charToValue(char c)
{
    // X ascii code is 88.
    return static_cast<int32_t>(c) - 87;
}

int32_t roundPoints(char c1, char c2)
{
    if (c1 == (c2 - ('X' - 'A')))
    {
        // Draw.
        return 3;
    }
    else if ((c1 == 'A' && c2 == 'Y') || (c1 == 'B' && c2 == 'Z') || (c1 == 'C' && c2 == 'X'))
    {
        // We won.
        return 6;
    }
    else
    {
        // We lost.
        return 0;
    }
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    int32_t totalScore{0};

    std::string line;
    while (std::getline(fileStream, line))
    {
        char c1{line[0]};
        char c2{line[2]};
        totalScore += charToValue(c2);
        totalScore += roundPoints(c1, c2);
    }

    std::cout << totalScore << '\n';

    return 0;
}
