//
// Created by Sergey Pankevich on 04.10.2021.
//

#pragma once

#include "Code.h"
#include "input_output.h"

class ArchiveWriter {
public:
    ArchiveWriter(std::ostream& output);
    ~ArchiveWriter();
    void Write9Bits(uint16_t value);
    void WriteCode(const Code& code);
    void WriteByte();
    void Flush();

private:
    void Write1Bit(bool bit);
    uint8_t written_bits_;
    uint8_t buffer_;
    std::ostream& output_;
};
