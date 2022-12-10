#include <algorithm>
#include <array>
#include <cmath>
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

    std::vector<Coord> rope;
    for (int i{0}; i < 9; ++i)
    {
        Coord c;
        c.x = 0;
        c.y = 0;
        rope.push_back(c);
    }

    std::vector<Coord> headVisited{};
    std::vector<Coord> tailVisitedUnique{};

    Coord head{};
    headVisited.push_back(head);
    tailVisitedUnique.push_back(head);

    std::string line;
    while (std::getline(fileStream, line))
    {
        int64_t repeat = std::stoi(line.substr(line.find(' ') + 1));

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

            // Update first knot of the rope.
            auto previousHeadPos = headVisited[headVisited.size() - 1];
            int64_t distX = head.x - rope[0].x;
            int64_t distY = head.y - rope[0].y;
            if (std::abs(distX) > 1 || std::abs(distY) > 1)
            {
                rope.at(0).x = previousHeadPos.x;
                rope.at(0).y = previousHeadPos.y;
            }

            // Update other knots.
            for (uint64_t i{1}; i < 9; ++i)
            {
                auto curr = rope.at(i);
                auto prev = rope.at(i - 1);
                int64_t ropeDistX = prev.x - curr.x;
                int64_t ropeDistY = prev.y - curr.y;

                // Check if touching.
                if (std::sqrt(ropeDistX * ropeDistX + ropeDistY * ropeDistY) <= std::sqrt(2))
                {
                    continue;
                }

                if (ropeDistX > 0)
                {
                    rope.at(i).x++;
                }
                else if (ropeDistX < 0)
                {
                    rope.at(i).x--;
                }

                if (ropeDistY > 0)
                {
                    rope.at(i).y++;
                }
                else if (ropeDistY < 0)
                {
                    rope.at(i).y--;
                }
            }

            auto tail = rope.at(rope.size() - 1);
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
