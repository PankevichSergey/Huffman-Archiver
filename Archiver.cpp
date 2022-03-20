//
// Created by Sergey Pankevich on 04.10.2021.
//

#include "Archiver.h"

#include "FileReader.h"

Archiver::Archiver(std::ostream& archive_stream, const std::vector<std::string_view>& files) : writer_(archive_stream) {
    for (size_t i = 0; i < files.size(); ++i) {
        ArchiveFile(files[i], i + 1 == files.size());
    }
    writer_.Flush();
}

void Archiver::CountSymbols(std::string_view file_name, FrequencyTable& frequency) {
    for (auto ch : file_name) {
        ++frequency[ch];
    }
    std::ifstream file_stream = OpenForReading(file_name);
    FileReader reader(file_stream);

    reader.ReadChar();
    while (reader.HaveCharsToRead()) {
        ++frequency[reader.GetChar()];
        reader.ReadChar();
    }

    file_stream.close();

    ++frequency[FILENAME_END];
    ++frequency[ARCHIVE_END];
    ++frequency[ONE_MORE_FILE];
}

void Archiver::ArchiveFile(std::string_view file_name, bool is_last_file) {
    FrequencyTable frequency;
    CountSymbols(file_name, frequency);

    Trie default_haffman_trie(frequency);
    Trie::Canonic canonic = default_haffman_trie.GetCanonicForm();
    Trie canonic_haffman_trie(canonic);
    Trie::CodesTable codes_table = canonic_haffman_trie.GetCodesTable();

    writer_.Write9Bits(canonic.order.size());
    for (uint16_t ch : canonic.order) {
        writer_.Write9Bits(ch);
    }
    for (uint16_t count : canonic.count_codes_of_length) {
        writer_.Write9Bits(count);
    }

    for (char ch : file_name) {
        writer_.WriteCode(codes_table[ch]);
    }
    writer_.WriteCode(codes_table[FILENAME_END]);

    std::ifstream file_stream = OpenForReading(file_name);
    FileReader reader(file_stream);

    reader.ReadChar();
    while (reader.HaveCharsToRead()) {
        writer_.WriteCode(codes_table[reader.GetChar()]);
        reader.ReadChar();
    }

    file_stream.close();

    if (is_last_file) {
        writer_.WriteCode(codes_table[ARCHIVE_END]);
    } else {
        writer_.WriteCode(codes_table[ONE_MORE_FILE]);
    }
}