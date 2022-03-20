//
// Created by Sergey Pankevich on 04.10.2021.
//

#pragma once

#include "ArchiveWriter.h"
#include "Trie.h"
#include "input_output.h"

class Archiver {
public:
    Archiver(std::ostream& archive_stream, const std::vector<std::string_view>& files);

private:
    void ArchiveFile(std::string_view file_name, bool is_last_file);

    void CountSymbols(std::string_view file_name, FrequencyTable&);

    ArchiveWriter writer_;
};
