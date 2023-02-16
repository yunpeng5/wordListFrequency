#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>

#include "file_reader.h"
#include "word_frequency_counter_concurrent.h"

void printWordFreqencyDesc(std::shared_ptr<std::unordered_map<std::string, unsigned int>> wordFreqMapPtr)
{
    std::vector<std::pair<std::string, unsigned int>> wordFreqList(wordFreqMapPtr->begin(), wordFreqMapPtr->end());
    std::sort(std::execution::par_unseq, wordFreqList.begin(), wordFreqList.end(),
        [](std::pair<std::string, unsigned int> left, std::pair<std::string, unsigned int> right)
        {
            return left.second == right.second ? left.first > right.first : left.second > right.second;
        });
    for (std::pair<std::string, unsigned int> wordFreqPair : wordFreqList)
    {
        std::cout << wordFreqPair.first << " " << wordFreqPair.second << std::endl;
    }
}

int main()
{
    std::unique_ptr<std::string> inputFileStringPtr = FileReader::readFileToString("wordlist.txt");
    WordFrequencyCounterConcurrent wordFrequencyCounter(std::move(inputFileStringPtr));
    std::shared_ptr<std::unordered_map<std::string, unsigned int>> wordFreqMapPtr = wordFrequencyCounter.getWordFrequencyMapPtr();
    printWordFreqencyDesc(wordFreqMapPtr);
    return 0;
}
