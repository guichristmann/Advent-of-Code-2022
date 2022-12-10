#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

struct Coord
{
    int64_t x, y;

    bool operator==(const Coord& other) { return (other.x == x) && (other.y == y); }
};

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    std::vector<Coord> headVisited{};
    std::vector<Coord> tailVisitedUnique{};

    Coord head{};
    Coord tail{};
    headVisited.push_back(head);
    tailVisitedUnique.push_back(tail);

    std::string line;
    while (std::getline(fileStream, line))
    {
        int32_t repeat = std::stoi(line.substr(line.find(' ') + 1));

        // int repeat{line[2] - '0'};

        while (repeat--)
        {
            // Update current position of head.
            if (line[0] == 'R')
            {
                head.x++;
            }
            else if (line[0] == 'L')
            {
                head.x--;
            }
            else if (line[0] == 'U')
            {
                head.y++;
            }
            else if (line[0] == 'D')
            {
                head.y--;
            }

            // Tail becomes previous head position.
            auto previousHeadPos = headVisited[headVisited.size() - 1];

            int32_t distX = head.x - tail.x;
            int32_t distY = head.y - tail.y;
            if (std::abs(distX) > 1 || std::abs(distY) > 1)
            {
                tail.x = previousHeadPos.x;
                tail.y = previousHeadPos.y;
            }

            if (std::find(tailVisitedUnique.begin(), tailVisitedUnique.end(), tail) == tailVisitedUnique.end())
            {
                tailVisitedUnique.push_back(tail);
            }

            headVisited.push_back(head);
        }
    }

    std::cout << tailVisitedUnique.size() << std::endl;

    return 0;
}
