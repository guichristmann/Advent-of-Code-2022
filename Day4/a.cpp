#include <fstream>
#include <iostream>
#include <string>

struct Assignment
{
    int64_t start, end, length;
};

// I would like to take a std::string_view but then converting to numeric types
// doesn't seem so easy? So const ref to string it is.
Assignment stringToAssignment(const std::string& str)
{
    auto splitIndex{str.find('-')};
    int64_t start{std::stoll(str.substr(0, splitIndex))};
    int64_t end{std::stoll(str.substr(splitIndex + 1))};

    return {start, end, end - start};
}

// Does const ref even help when the struct is just three int64?
bool assignmentsOverlap(const Assignment& shorter, const Assignment& other)
{
    return (shorter.start >= other.start) && (shorter.end <= other.end);
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    int64_t overlapCount{0};

    std::string line;
    while (std::getline(fileStream, line))
    {
        auto splitIndex{line.find(',')};

        Assignment assignment1{stringToAssignment(line.substr(0, splitIndex))};
        Assignment assignment2{stringToAssignment(line.substr(splitIndex + 1))};

        bool overlap{};
        if (assignment1.length < assignment2.length)
        {
            overlap = assignmentsOverlap(assignment1, assignment2);
        }
        else
        {
            overlap = assignmentsOverlap(assignment2, assignment1);
        }

        if (overlap)
        {
            overlapCount++;
        }
    }

    std::cout << overlapCount << " assignments overlap." << std::endl;

    return 0;
}
