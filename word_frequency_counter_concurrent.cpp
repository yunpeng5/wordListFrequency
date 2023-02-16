#include "word_frequency_counter_concurrent.h"

#include <thread>
#include <vector>
#include <thread>
#include <algorithm>
#include <cctype>

WordFrequencyCounterConcurrent::WordFrequencyCounterConcurrent(std::shared_ptr<std::string> inputStringPtr) :
    wordStringPtr(std::move(inputStringPtr)),
    wordFreqPtr(std::make_shared<std::unordered_map<std::string, unsigned int>>()),
    isFrequencyCounted(false) {}

void WordFrequencyCounterConcurrent::calculateFrequency()
{
    unsigned int numThreads = std::thread::hardware_concurrency();
    unsigned int numCharPerThread = std::max((unsigned int)wordStringPtr->size() / numThreads, 1U);
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < wordStringPtr->size(); i += numCharPerThread)
    {
        unsigned int leftBound = i;
        unsigned int rightBound = std::min(i + numCharPerThread - 1, (unsigned int)wordStringPtr->size() - 1);
        threads.push_back(std::thread(&WordFrequencyCounterConcurrent::concurrentCountWorker, this, leftBound, rightBound));
    }
    for (unsigned int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
    isFrequencyCounted = true;
}

std::shared_ptr<std::unordered_map<std::string, unsigned int>> WordFrequencyCounterConcurrent::getWordFrequencyMapPtr()
{
    if (!isFrequencyCounted)
    {
        calculateFrequency();
    }
    return wordFreqPtr;
}

void WordFrequencyCounterConcurrent::concurrentCountWorker(unsigned int leftBound, unsigned int rightBound)
{
    leftBound = getLeftBoundAvoidWordBreak(leftBound);
    rightBound = getRightBoundAvoidWordBreak(rightBound);
    std::unordered_map<std::string, unsigned int> localWordFreq;
    std::string currentWord;
    for (unsigned int i = leftBound; i <= rightBound && i < wordStringPtr->size(); i++)
    {
        char currentChar = (*wordStringPtr)[i];
        if (isDelimiter(currentChar))
        {
            if (currentWord != "")
            {
                convertToLowerCase(currentWord);
                localWordFreq[currentWord]++;
                currentWord = "";
            }
            continue;
        }
        currentWord.push_back(currentChar);
    }
    if (currentWord != "")
    {
        convertToLowerCase(currentWord);
        localWordFreq[currentWord]++;
    }
    writeLocalResultToWordFreq(localWordFreq);
}

unsigned int WordFrequencyCounterConcurrent::getLeftBoundAvoidWordBreak(unsigned int leftBound)
{
    if (leftBound == 0 || isDelimiter((*wordStringPtr)[leftBound]) || isDelimiter((*wordStringPtr)[leftBound - 1]))
    {
        return leftBound;
    }
    while (leftBound < wordStringPtr->size() && !isDelimiter((*wordStringPtr)[leftBound]))
    {
        leftBound++;
    }
    return leftBound;
}

unsigned int WordFrequencyCounterConcurrent::getRightBoundAvoidWordBreak(unsigned int rightBound)
{
    if (rightBound == wordStringPtr->size() - 1 || isDelimiter((*wordStringPtr)[rightBound]) || isDelimiter((*wordStringPtr)[rightBound + 1]))
    {
        return rightBound;
    }
    while (rightBound < wordStringPtr->size() && !isDelimiter((*wordStringPtr)[rightBound]))
    {
        rightBound++;
    }
    return rightBound;
}

bool WordFrequencyCounterConcurrent::isDelimiter(char character)
{
    return character == ' ' || character == '\n';
}

void WordFrequencyCounterConcurrent::writeLocalResultToWordFreq(const std::unordered_map<std::string, unsigned int> &localResult)
{
    std::lock_guard<std::mutex> wordFreqWriteLock(wordFreqWriteMutex);
    for (std::pair<std::string, int> wordFreqPair : localResult)
    {
        (*wordFreqPtr)[wordFreqPair.first] += wordFreqPair.second;
    }
}

void WordFrequencyCounterConcurrent::convertToLowerCase(std::string &inputString)
{
    std::transform(inputString.begin(), inputString.end(), inputString.begin(), [](char c)
        {
            return std::tolower(c);
        });
}
