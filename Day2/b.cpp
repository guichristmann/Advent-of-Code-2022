#include <fstream>
#include <iostream>
#include <string>

int32_t charToValue(char c)
{
    // X ascii code is 88.
    return static_cast<int32_t>(c) - 87;
}

char toLose(char c)
{
    if (c == 'A')
    {
        return 'Z';
    }
    else if (c == 'B')
    {
        return 'X';
    }
    else
    {
        return 'Y'; 
    }
}

char toWin(char c)
{
    if (c == 'A')
    {
        return 'Y';
    }
    else if (c == 'B')
    {
        return 'Z';
    }
    else
    {
        return 'X';
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

        int32_t roundPoints{(charToValue(c2) - 1) * 3};

        char toPlay{};
        if (c2 == 'X')
        {
            toPlay = toLose(c1); 
        }
        else if (c2 == 'Y')
        {
            toPlay = c1 + ('X' - 'A');
        }
        else
        {
            toPlay = toWin(c1);
        }

        totalScore += roundPoints;
        totalScore += charToValue(toPlay);
    }

    std::cout << totalScore << '\n';

    return 0;
}
