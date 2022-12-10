#include <fstream>
#include <iostream>
#include <string>

void updateStrength(int64_t cycles, int64_t registerV, int64_t& accum)
{
    if (cycles == 20 || (cycles > 20 && (cycles - 20) % 40 == 0))
    {
        int64_t strength = static_cast<int64_t>(cycles) * registerV;
        accum += strength;
    }
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    int64_t registerValue{1};
    uint64_t cycles{0};

    int64_t accumStrength{0};

    std::string line;
    while (std::getline(fileStream, line))
    {
        auto space = line.find(' ');
        std::string op{line.substr(0, space)};

        if (op == "noop")
        {
            cycles++;
            updateStrength(static_cast<int64_t>(cycles), registerValue, accumStrength);
        }
        else if (op == "addx")
        {
            cycles++;
            updateStrength(static_cast<int64_t>(cycles), registerValue, accumStrength);

            cycles++;
            int64_t operand{std::stoi(line.substr(space + 1))};
            updateStrength(static_cast<int64_t>(cycles), registerValue, accumStrength);
            registerValue += operand;
        }
    }

    std::cout << accumStrength << std::endl;

    return 0;
}
