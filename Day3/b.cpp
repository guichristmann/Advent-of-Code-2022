#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>

char findCommon(std::string_view first, std::string_view second, std::string_view third)
{
    for (auto c : first)
    {
        if (std::find(second.begin(), second.end(), c) == second.end())
            continue; // Keep searching.
        else if (std::find(third.begin(), third.end(), c) == third.end())
            continue; // Keep searching.
        else
            return c; // Found it.
    }

    assert(false); // Should never reach it.

    return {};
}

int64_t charToValue(char c)
{
    if (c >= 'a')
    {
        return c - 'a' + 1;
    }
    else
    {
        return c - 'A' + 27;
    }
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    int64_t sumOfPriorities{0};

    std::string firstLine;    
    std::string secondLine;    
    std::string thirdLine;    
    while (std::getline(fileStream, firstLine))
    {
        std::getline(fileStream, secondLine);
        std::getline(fileStream, thirdLine);

        char common{findCommon(firstLine, secondLine, thirdLine)};

        sumOfPriorities += charToValue(common);
    }

    std::cout << sumOfPriorities << '\n';

    return 0;
}
