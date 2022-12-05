#include <array>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

struct Command
{
    int32_t n, from, to;
};

using CrateStack = std::vector<char>;

constexpr int32_t numberOfStacks = 9;  // 3 for example, 9 for input.

std::array<CrateStack, numberOfStacks> initStacks(std::ifstream& fs)
{
    std::array<CrateStack, numberOfStacks> stacks;

    std::string line;
    while (std::getline(fs, line))
    {
        if (line[1] == '1')
        {
            std::cout << "Finished reading initial stacks.\n";
            break;
        }

        for (uint32_t i{0}; i < numberOfStacks; ++i)
        {
            // There's an offset of 4 characters between each initial crate.
            char crate{line[1 + i * 4]};

            // Check if not a space character.
            if (crate != 32)
            {
                stacks[i].push_back(crate);
            }
        }
    }

    return stacks;
}

Command extractCommandFromString(const std::string& str)
{
    auto space1{str.find(' ')};
    auto space2{str.find(' ', space1 + 1)};
    int32_t first{std::stoi(str.substr(space1 + 1, space2 - space1))};

    space1 = str.find(' ', space2 + 1);
    space2 = str.find(' ', space1 + 1);
    int32_t second{std::stoi(str.substr(space1 + 1, space2 - space1))};

    space1 = str.find(' ', space2 + 1);
    space2 = str.find(' ', space1 + 1);
    int32_t third{std::stoi(str.substr(space1 + 1, space2 - space1))};

    // Indexes shift down by 1.
    return {first, second - 1, third - 1};
}

void printStacks(const std::array<CrateStack, numberOfStacks>& stacks)
{
    for (const auto& stack : stacks)
    {
        for (const char crate : stack)
        {
            std::cout << crate << std::endl;
        }
        std::cout << "----\n";
    }
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    auto stacks = initStacks(fileStream);

    std::string line;
    // Throaway getline, skipping empty line.
    std::getline(fileStream, line);

    while (std::getline(fileStream, line))
    {
        Command cmd{extractCommandFromString(line)};

        // Grab ref to relevant crate stacks.
        CrateStack& from = stacks[static_cast<uint32_t>(cmd.from)];
        CrateStack& to = stacks[static_cast<uint32_t>(cmd.to)];

        while (cmd.n--)
        {
            auto offset = static_cast<uint32_t>(cmd.n);
            char crate{from[offset]};
            from.erase(from.begin() + offset);
            to.insert(to.begin(), crate);
        }
    }

    std::cout << "Final arrangement code: \n";
    for (const auto& stack : stacks)
    {
        std::cout << stack[0];
    }

    std::cout << std::endl;

    return 0;
}
