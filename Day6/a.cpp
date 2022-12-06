#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

std::optional<int32_t> findRepeatIndex(std::string_view str)
{
    for (uint32_t i{0}; i < str.length(); ++i)
    {
        for (uint32_t j{0}; j < str.length(); ++j)
        {
            if (i == j)
            {
                continue;
            }

            if (str[i] == str[j])
            {
                return static_cast<int32_t>(i);
            }
        }
    }

    return {};
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");
    std::string line;
    std::getline(fileStream, line);

    uint32_t indexStartOfPacket{0};
    for (; indexStartOfPacket < line.length() - 3; ++indexStartOfPacket)
    {
        std::string currBuf{line.substr(indexStartOfPacket, 4)};
        if (auto repeatIndex = findRepeatIndex(currBuf))
        {
            indexStartOfPacket += static_cast<uint32_t>(repeatIndex.value());
        }
        else
        {
            break;
        }
    }

    std::cout << indexStartOfPacket + 4 << " characters processed before start-of-packet." << std::endl;

    return 0;
}
