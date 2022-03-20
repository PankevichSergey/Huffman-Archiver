//
// Created by Sergey Pankevich on 04.10.2021.
//

#pragma once

#include "ArchiveReader.h"
#include "Trie.h"

class Unarchiver {
public:
    Unarchiver(std::istream& arhive_name);

private:
    std::string GetFileName(Trie& trie);
    Trie::Canonic ReadCanonic();
    bool UnarchiveFile();
    ArchiveReader reader_;
};
