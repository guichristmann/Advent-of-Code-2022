#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using TreeMap = std::vector<std::vector<uint16_t>>;

bool isVisible(const TreeMap& map, uint64_t y, uint64_t x)
{
    uint16_t treeHeight{map[y][x]};

    bool success = true;
    for (int64_t s_y{y + 1}; s_y < map.size(); ++s_y)
    {
        if (map[s_y][x] >= treeHeight)
        {
            success = false;
            break;
        }
    }
    if (success)
    {
        return true;
    }

    success = true;
    for (int64_t s_y{y - 1}; s_y >= 0; --s_y)
    {
        if (map[s_y][x] >= treeHeight)
        {
            success = false;
            break;
        }
    }
    if (success)
    {
        return true;
    }

    success = true;
    for (int64_t s_x{x - 1}; s_x >= 0; --s_x)
    {
        if (map[y][s_x] >= treeHeight)
        {
            success = false;
            break;
        }
    }
    if (success)
    {
        return true;
    }

    success = true;
    for (int64_t s_x{x + 1}; s_x < map[0].size(); ++s_x)
    {
        if (map[y][s_x] >= treeHeight)
        {
            success = false;
            break;
        }
    }
    if (success)
    {
        return true;
    }

    return false;
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    TreeMap treeMap;

    std::string line;
    while (std::getline(fileStream, line))
    {
        std::vector<uint16_t> row;
        for (const char c : line)
        {
            auto v = static_cast<uint16_t>(c - '0');
            row.push_back(v);
        }

        treeMap.push_back(row);
    }

    uint64_t countVisible{0};
    // Edges.
    countVisible += (treeMap.size() * 2) - 2;
    countVisible += (treeMap[0].size() * 2) - 2;

    for (uint64_t y{1}; y < treeMap.size() - 1; ++y)
    {
        for (uint64_t x{1}; x < treeMap[0].size() - 1; ++x)
        {
            countVisible += isVisible(treeMap, y, x);
        }
    }

    std::cout << countVisible << std::endl;

    return 0;
}
