#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr uint64_t cols{40};
constexpr uint64_t rows{6};

void updateStrength(int64_t cycles, int64_t registerV, int64_t& accum)
{
    if (cycles == 20)
    {
        int64_t strength = static_cast<int64_t>(cycles) * registerV;
        accum += strength;
    }
    else if (cycles > 20 && (cycles - 20) % 40 == 0)
    {
        int64_t strength = static_cast<int64_t>(cycles) * registerV;
        accum += strength;
    }
}

void pixelCheck(uint64_t cycles, std::array<std::array<char, cols>, rows>& img, int64_t registerValue)
{
    uint64_t pixelCol{cycles % cols};
    uint64_t pixelRow{cycles / cols};

    if (std::abs(registerValue - pixelCol) <= 1)
    {
        img.at(pixelRow).at(pixelCol) = '#';
    }
}

void printImg(const std::array<std::array<char, cols>, rows>& img)
{
    for (uint64_t r{0}; r < rows; ++r)
    {
        for (uint64_t c{0}; c < cols; ++c)
        {
            std::cout << img[r][c];
        }
        std::cout << '\n';
    }
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    int64_t registerValue{1};
    uint64_t cycles{0};

    std::array<std::array<char, cols>, rows> img;

    for (uint64_t r{0}; r < rows; ++r)
    {
        for (uint64_t c{0}; c < cols; ++c)
        {
            img[r][c] = '.';
        }
    }

    std::string line;
    while (std::getline(fileStream, line))
    {
        auto space = line.find(' ');
        std::string op{line.substr(0, space)};

        if (op == "noop")
        {
            pixelCheck(cycles, img, registerValue);
            cycles++;
        }
        else if (op == "addx")
        {
            pixelCheck(cycles, img, registerValue);
            cycles++;

            pixelCheck(cycles, img, registerValue);
            cycles++;
            int64_t operand{std::stoi(line.substr(space + 1))};
            registerValue += operand;
        }
    }

    printImg(img);

    return 0;
}
