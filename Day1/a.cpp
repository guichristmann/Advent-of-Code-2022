#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    int64_t mostCalories{0};
    int64_t currCalories{0};

    std::string line;
    while (std::getline(fileStream, line))
    {
        if (line == "")
        {
            if (currCalories > mostCalories)
            {
                mostCalories = currCalories;
            }
            currCalories = 0;
        }
        else
        {
            currCalories += std::stoll(line);
        }
    }
    if (currCalories > mostCalories)
    {
        mostCalories = currCalories;
    }

    std::cout << "The most calories carried by an elf is " << mostCalories << " calories.\n";

    return 0;
}
