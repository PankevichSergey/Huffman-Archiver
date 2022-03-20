#include <iostream>

#include "Archiver.h"
#include "ArgumentsParser.h"
#include "FeedbackWriter.h"
#include "Unarchiver.h"
#include "input_output.h"

int main(int argc, char** argv) {
    FeedbackWriter feedback_writer(std::cout);
    try {
        ArgumentsParser parser(argc, argv);

        if (parser.GetMode() == ArgumentsParser::Mode::HELP) {
            feedback_writer.WriteHelpInfo();
        } else if (parser.GetMode() == ArgumentsParser::Mode::ARCHIVE) {
            std::ofstream archive_stream = OpenForWriting(parser.GetArchiveName());
            Archiver archiver(archive_stream, parser.GetFiles());
            archive_stream.close();
            feedback_writer.CreatedArchive();
        } else {
            std::ifstream archive_stream = OpenForReading(parser.GetArchiveName());
            Unarchiver unarchiver(archive_stream);
            archive_stream.close();
            feedback_writer.ExtractedFiles();
        }
        return 0;
    } catch (const std::invalid_argument& error) {
        feedback_writer.WriteError(error.what());
        return 1;
    } catch (const std::logic_error& error) {
        feedback_writer.WriteError("archiver's algorithm crushed");
        return 1;
    } catch (...) {
        feedback_writer.WriteError("unknown error");
        return 1;
    }
}
