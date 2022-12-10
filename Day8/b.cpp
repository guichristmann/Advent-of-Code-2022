#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using TreeMap = std::vector<std::vector<uint16_t>>;

uint64_t scenicScore(const TreeMap& map, uint64_t y, uint64_t x)
{
    uint16_t treeHeight{map[y][x]};
    uint64_t leftScore{1};
    uint64_t rightScore{1};
    uint64_t upScore{1};
    uint64_t downScore{1};

    for (int64_t s_y{y + 1}; s_y < map.size(); ++s_y)
    {
        if (map[s_y][x] >= treeHeight)
        {
            break;
        }
        if (s_y + 1 < map.size())
        {
            downScore++;
        }
    }

    for (int64_t s_y{y - 1}; s_y >= 0; --s_y)
    {
        if (map[s_y][x] >= treeHeight)
        {
            break;
        }
        if (s_y - 1 >= 0)
        {
            upScore++;
        }
    }

    for (int64_t s_x{x - 1}; s_x >= 0; --s_x)
    {
        if (map[y][s_x] >= treeHeight)
        {
            break;
        }
        if (s_x - 1 >= 0)
        {
            leftScore++;
        }
    }

    for (int64_t s_x{x + 1}; s_x < map[0].size(); ++s_x)
    {
        if (map[y][s_x] >= treeHeight)
        {
            break;
        }
        if (s_x + 1 < map[0].size())
        {
            rightScore++;
        }
    }

    return leftScore * rightScore * upScore * downScore;
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

    uint64_t bestScenicScore{0};
    for (uint64_t y{1}; y < treeMap.size() - 1; ++y)
    {
        for (uint64_t x{1}; x < treeMap[0].size() - 1; ++x)
        {
            uint64_t score{scenicScore(treeMap, y, x)};
            if (score > bestScenicScore)
            {
                bestScenicScore = score;
            }
        }
    }

    std::cout << bestScenicScore << std::endl;

    return 0;
}
