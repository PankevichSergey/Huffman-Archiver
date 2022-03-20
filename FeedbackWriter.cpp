//
// Created by Sergey Pankevich on 11.10.2021.
//

#include "FeedbackWriter.h"

FeedbackWriter::FeedbackWriter(std::ostream& output) : output_(output) {}

void FeedbackWriter::WriteHelpInfo() {
    output_ << "NAME" << std::endl
            << std::endl
            << "archiver -- archive and unarhive files" << std::endl
            << std::endl
            << "SYNOPSIS" << std::endl
            << std::endl
            << "archiver -c archive_name file1 [file2 ...]" << std::endl
            << "archiver -d archive_name" << std::endl
            << "archiver -h" << std::endl
            << std::endl
            << "DESCRIPTION" << std::endl
            << std::endl
            << "-c   compress files file1, file2, ... into archive archive_name" << std::endl
            << "-d   decompress files from archive_name and save them with initial names" << std::endl
            << "-h   show usage" << std::endl;
}

void FeedbackWriter::WriteError(std::string_view error) {
    output_ << "Error occurred: " << error << std::endl;
}

void FeedbackWriter::CreatedArchive() {
    output_ << "Archive was successfully created" << std::endl;
}

void FeedbackWriter::ExtractedFiles() {
    output_ << "Files were successfully created" << std::endl;
}