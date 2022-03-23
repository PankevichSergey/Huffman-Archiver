//
// Created by Sergey Pankevich on 04.10.2021.
//

#include "ArgumentsParser.h"
#include <string>

ArgumentsParser::ArgumentsParser(int argc, char** argv) {
    if (argc == 1) {
        throw std::invalid_argument("archiver mode is not chosen");
    }
    std::string mode_argument(argv[1]);
    if (mode_argument == "-d") {
        mode = Mode::UNARCHIVE;
        if (argc == 2) {
            throw std::invalid_argument("archive name is not provided");
        }
        if (argc > 3) {
            throw std::invalid_argument("too many arguments");
        }
    } else if (mode_argument == "-c") {
        mode = Mode::ARCHIVE;
        if (argc == 2) {
            throw std::invalid_argument("archive name is not provided");
        }
        if (argc == 3) {
            throw std::invalid_argument("files are not chosen");
        }
    } else if (mode_argument == "-h") {
        mode = Mode::HELP;
        if (argc > 2) {
            throw std::invalid_argument("too many arguments");
        }
    } else {
        throw std::invalid_argument("invalid archiver mode");
    }
    if (argc >= 3) {
        archive_name = argv[2];
    }
    for (size_t i = 3; i < argc; ++i) {
        files.push_back(argv[i]);
    }
}

ArgumentsParser::Mode ArgumentsParser::GetMode() const {
    return mode;
}

const std::vector<std::string_view>& ArgumentsParser::GetFiles() const {
    return files;
}

const std::string_view& ArgumentsParser::GetArchiveName() const {
    return archive_name;
}
