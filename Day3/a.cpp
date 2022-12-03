#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <cassert>

char findCommon(std::string_view first, std::string_view second)
{
    for (auto c1 : first)
    {
        for (auto c2 : second)
        {
            if (c1 == c2)
                return c1;
        }
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

    std::string line;    
    while (std::getline(fileStream, line))
    {
        uint64_t n{line.size()};
        std::string firstCompartment{line.substr(0, n / 2)};
        std::string secondCompartment{line.substr(n / 2)};

        char common{findCommon(firstCompartment, secondCompartment)};

        sumOfPriorities += charToValue(common);
    }

    std::cout << sumOfPriorities << '\n';

    return 0;
}
