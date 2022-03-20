//
// Created by Sergey Pankevich on 04.10.2021.
//

#pragma once

#include <string_view>
#include <vector>

class ArgumentsParser {
public:
    enum class Mode { ARCHIVE, UNARCHIVE, HELP };
    ArgumentsParser(int argc, char** argv);
    Mode GetMode() const;
    const std::vector<std::string_view>& GetFiles() const;
    const std::string_view& GetArchiveName() const;

private:
    Mode mode;
    std::vector<std::string_view> files;
    std::string_view archive_name;
};
