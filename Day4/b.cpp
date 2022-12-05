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
bool assignmentsOverlap(const Assignment& a, const Assignment& b)
{
    return ((a.start >= b.start) && (a.start <= b.end)) || ((a.end <= b.end) && (a.end >= b.start)) ||
           ((b.start >= a.start) && (b.start <= a.end)) || ((b.end <= a.end) && (b.end >= a.start));
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

        if (assignmentsOverlap(assignment1, assignment2))
        {
            overlapCount++;
        }
    }

    std::cout << overlapCount << " assignments overlap." << std::endl;

    return 0;
}
