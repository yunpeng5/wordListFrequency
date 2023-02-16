#ifndef WORD_FREQUENCY_COUNTER_CONCURRENT_H
#define WORD_FREQUENCY_COUNTER_CONCURRENT_H

#include <string>
#include <memory>
#include <unordered_map>
#include <mutex>

class WordFrequencyCounterConcurrent
{
public:
    // Construct the word frequency counter obj with input string pointer
    WordFrequencyCounterConcurrent(std::shared_ptr<std::string> inputStringPtr);
    // Calculate the word frequency of the input string
    void calculateFrequency();
    // Get a pointer to word frequency map of the input string
    std::shared_ptr<std::unordered_map<std::string, unsigned int>> getWordFrequencyMapPtr();

private:
    std::shared_ptr<std::string> wordStringPtr;
    std::shared_ptr<std::unordered_map<std::string, unsigned int>> wordFreqPtr;
    std::mutex wordFreqWriteMutex;
    bool isFrequencyCounted;

    void concurrentCountWorker(unsigned int leftBound, unsigned int rightBound);
    unsigned int getLeftBoundAvoidWordBreak(unsigned int leftBound);
    unsigned int getRightBoundAvoidWordBreak(unsigned int rightBound);
    bool isDelimiter(char character);
    void writeLocalResultToWordFreq(const std::unordered_map<std::string, unsigned int> &localResult);
    void convertToLowerCase(std::string& inputString);
};

#endif // WORD_FREQUENCY_COUNTER_CONCURRENT_H
