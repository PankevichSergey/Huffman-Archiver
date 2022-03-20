//
// Created by Sergey Pankevich on 11.10.2021.
//

#pragma once

#include <iostream>

class FeedbackWriter {
public:
    FeedbackWriter(std::ostream& output);
    void WriteError(std::string_view error);
    void CreatedArchive();
    void ExtractedFiles();
    void WriteHelpInfo();

private:
    std::ostream& output_;
};
