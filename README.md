# wordListFrequency
This project uses a fileReader to read all wordlist.txt file content into a string. Then it uses WordFrequencyCounterConcurrent to read the string and count the word frequency in parallel. Afterwards, main function will call printWordFreqencyDesc to sort the frequence in parallel and output the result.

This project complies successfully on Windows10 version 21H2 using MingW-W64 version 10.0.0 (GCC 12.2.0). Please modify the Makefile and uses latest GCC if you'd like to compile it on other systems.