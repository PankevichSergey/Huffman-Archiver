add_executable(archiver
        main.cpp
        ArgumentsParser.cpp ArgumentsParser.h Archiver.cpp Archiver.h Unarchiver.cpp Unarchiver.h ArchiveReader.cpp ArchiveReader.h ArchiveWriter.cpp ArchiveWriter.h input_output.h Trie.cpp Trie.h TrieNode.cpp TrieNode.h Heap.h Heap.cpp FileReader.cpp FileReader.h Code.cpp Code.h FileWriter.cpp FileWriter.h input_output.cpp input_output.cpp FeedbackWriter.cpp FeedbackWriter.h)


project(archiver)

cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)