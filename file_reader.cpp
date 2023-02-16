#include "file_reader.h"

#include <fstream>

std::unique_ptr<std::string> FileReader::readFileToString(std::string fileName)
{
    std::ifstream inputFileStream(fileName);
    if (!inputFileStream)
    {
        throw std::runtime_error("Cannot open file" + fileName);
    }
    inputFileStream.seekg(0, std::ios::end);
    size_t inputFileSize = inputFileStream.tellg();
    std::unique_ptr<std::string> fileStringPtr = std::make_unique<std::string>(inputFileSize, ' ');
    inputFileStream.seekg(0);
    inputFileStream.read(fileStringPtr->data(), inputFileSize);
    return fileStringPtr;
}
