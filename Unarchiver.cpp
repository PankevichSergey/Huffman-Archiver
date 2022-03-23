//
// Created by Sergey Pankevich on 04.10.2021.
//

#include "Unarchiver.h"

#include "FileWriter.h"

Trie::Canonic Unarchiver::ReadCanonic() {
    uint16_t symbols_count = reader_.Read9Bits();
    Trie::Canonic canonic;
    for (uint16_t i = 0; i < symbols_count; ++i) {
        canonic.order.push_back(reader_.Read9Bits());
    }
    while (symbols_count > 0) {
        canonic.count_codes_of_length.push_back(reader_.Read9Bits());
        symbols_count -= canonic.count_codes_of_length.back();
    }
    return canonic;
}

std::string Unarchiver::GetFileName(Trie& canonic_haffman_trie) {
    std::string file_name;
    std::vector<int> turns;
    auto pog = canonic_haffman_trie.GetCodesTable();
    while (true) {
        turns.push_back(reader_.Read1Bit());
        //canonic_haffman_trie.MoveState(reader_.Read1Bit());
        canonic_haffman_trie.MoveState(turns.back());
        if (canonic_haffman_trie.ReachedTerminal()) {
            if (canonic_haffman_trie.GetStateValue() == FILENAME_END) {
                break;
            }
            file_name += canonic_haffman_trie.GetStateValue();
            turns.clear();
        }
    }
    return file_name;
}

bool Unarchiver::UnarchiveFile() {
    Trie canonic_haffman_trie(ReadCanonic());
    std::ofstream file_output = OpenForWriting(GetFileName(canonic_haffman_trie));
    FileWriter file_writer(file_output);
    while (true) {
        canonic_haffman_trie.MoveState(reader_.Read1Bit());
        if (canonic_haffman_trie.ReachedTerminal()) {
            if (canonic_haffman_trie.GetStateValue() == ONE_MORE_FILE) {
                return true;
            }
            if (canonic_haffman_trie.GetStateValue() == ARCHIVE_END) {
                return false;
            }
            file_writer.WriteChar(canonic_haffman_trie.GetStateValue());
        }
    }
    file_writer.Flush();
    file_output.close();
}

Unarchiver::Unarchiver(std::istream& archive_stream) : reader_(archive_stream) {
    bool one_more_file = true;
    while (one_more_file) {
        one_more_file = UnarchiveFile();
    }
}