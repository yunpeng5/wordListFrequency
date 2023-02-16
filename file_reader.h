#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <memory>

class FileReader
{
public:
    // Read the a file and return the string containing the file content
    static std::unique_ptr<std::string> readFileToString(std::string fileName);
};

#endif // FILE_READER_H
