WA:=-Wall -Wextra -DNDEBUG

all: wordListFrequency.cpp file_reader.cpp file_reader.h word_frequency_counter_concurrent.cpp word_frequency_counter_concurrent.h
	g++ -std=c++17 -O2 -o wordListFrequency wordListFrequency.cpp file_reader.cpp word_frequency_counter_concurrent.cpp $(WA)