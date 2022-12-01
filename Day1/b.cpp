#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void checkReplace(std::vector<int64_t>& v, int64_t val)
{
    if (val > v[0])
    {
        v[0] = val;
    }

    std::sort(v.begin(), v.end());
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    std::vector<int64_t> topThreeCalories{{0, 0, 0}};
    int64_t currCalories{0};

    std::string line;
    while (std::getline(fileStream, line))
    {
        if (line == "")
        {
            checkReplace(topThreeCalories, currCalories);
            currCalories = 0;
        }
        else
        {
            currCalories += std::stoll(line);
        }
    }
    checkReplace(topThreeCalories, currCalories);

    std::cout << "Top three calories: " << topThreeCalories[0] << ", " << topThreeCalories[1] << ", "
              << topThreeCalories[2] << '\n';

    std::cout << "Total: " << std::accumulate(topThreeCalories.begin(), topThreeCalories.end(), 0) << '\n';

    return 0;
}
