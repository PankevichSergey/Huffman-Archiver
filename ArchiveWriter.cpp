//
// Created by Sergey Pankevich on 04.10.2021.
//

#include "ArchiveWriter.h"

ArchiveWriter::ArchiveWriter(std::ostream& output) : written_bits_(0), buffer_(0), output_(output) {}

void ArchiveWriter::WriteByte() {
    if (written_bits_ == 0) {
        return;
    }
    written_bits_ = 0;
    output_ << buffer_;
    buffer_ = 0;
}

void ArchiveWriter::Flush() {
    WriteByte();
    output_.flush();
}

ArchiveWriter::~ArchiveWriter() {
    Flush();
}

void ArchiveWriter::Write1Bit(bool bit) {
    if (written_bits_ == BITS_IN_CHAR) {
        WriteByte();
    }
    if (bit) {
        buffer_ ^= 1u << written_bits_;
    }
    ++written_bits_;
}

void ArchiveWriter::WriteCode(const Code& code) {
    for (uint8_t i = 0; i < code.length; ++i) {
        Write1Bit((code.code >> i) & 1);
    }
}

void ArchiveWriter::Write9Bits(uint16_t value) {
    for (uint8_t i = 0; i < 9; ++i) {
        Write1Bit((value >> i) & 1);
    }
}
