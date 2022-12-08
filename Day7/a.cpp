#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

constexpr uint64_t puzzleMaxSize{100'000};

enum Type : int
{
    directory,
    file
};

struct FileSystemNode
{
    std::string name;
    Type type;
    uint64_t size;

    FileSystemNode* parent;
    std::vector<FileSystemNode> children;

    FileSystemNode() = delete;
    FileSystemNode(const std::string& name) : name{name}, type{}, size{0}, parent{nullptr} {}

    ~FileSystemNode() {}
};

FileSystemNode rootfs("/");

FileSystemNode* cd(const std::string& str, FileSystemNode* currNode)
{
    // Retrieve the directory argument.
    std::string arg{str.substr(3)};

    // Change directory to pointed by arg.
    if (arg == "/")
    {
        // Special case for root directory.
        currNode = &rootfs;
    }
    else if (arg == "..")
    {
        // Go up one directory.
        currNode = currNode->parent;
    }
    else
    {
        // Find directory among children of currNode.
        auto cmp = [arg](const FileSystemNode& n) { return n.name == arg; };
        auto itr = std::find_if(currNode->children.begin(), currNode->children.end(), cmp);
        if (itr != currNode->children.end())
        {
            // Oh wow look at this, isn't it ugly?
            currNode = &(*itr);
        }
        else
        {
            assert(false && "Trying to cd into an unknown directory.");
        }
    }

    return currNode;
}

void ls(FileSystemNode* node, std::ifstream& stream)
{
    std::string line;
    while (std::getline(stream, line))
    {
        auto spaceIndex{line.find(' ')};
        std::string s1{line.substr(0, spaceIndex)};
        std::string s2{line.substr(spaceIndex + 1)};

        if (s1 == "dir")
        {
            FileSystemNode newNode(s2);
            newNode.parent = node;
            newNode.type = directory;
            node->children.push_back(newNode);
        }
        else
        {
            FileSystemNode newNode(s2);
            newNode.parent = node;
            newNode.type = file;
            newNode.size = std::stoul(s1);
            node->children.push_back(newNode);
        }

        if (stream.peek() == '$')
        {
            break;
        }
    }
}

uint64_t recurseSizesAndSolvePuzzle(FileSystemNode* node, uint64_t& solution)
{
    if (node->type == file)
    {
        return node->size;
    }
    else if (node->type == directory)
    {
        for (auto& c : node->children)
        {
            node->size += recurseSizesAndSolvePuzzle(&c, solution);
        }
    }

    if (node->size <= puzzleMaxSize)
    {
        solution += node->size;
    }
    
    return node->size;
}

int main()
{
    std::ifstream fileStream;
    fileStream.open("input.txt");

    FileSystemNode* currNode{&rootfs};

    std::string line;
    while (std::getline(fileStream, line))
    {
        // Skip "$ ".
        line = line.substr(2);

        // Next two characters are the command: ls or cd.
        std::string cmd{line.substr(0, 2)};
        if (cmd == "cd")
        {
            currNode = cd(line, currNode);
        }
        else if (cmd == "ls")
        {
            // The next lines until a '$' character and fills out the
            // directory under `currNode`.
            ls(currNode, fileStream);
        }
        else
        {
            assert(false && "Tried to execute invalid command. I can only handle cd or ls.");
        }
    }

    uint64_t solution{0};
    recurseSizesAndSolvePuzzle(&rootfs, solution);

    std::cout << "The solution to the puzzle is " << solution << std::endl;

    return 0;
}
