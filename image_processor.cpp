#include <iostream>

#include "Command_line/CommandLine.h"
#include "Controller/Controller.h"
#include "File_Interaction/Reader.h"
#include "File_Interaction/Writer.h"

int main(int argc, char* argv[]) {
    try {
        auto command_line = CommandLine(argc, argv);
        auto image = ReadImageFromFile(command_line.GetFileIn(), command_line.GetFileInResolution());
        FilterController filter_controller(&image, command_line.GetFilters());
        filter_controller.DoFilters();
        WriteFileFromImage(command_line.GetFileOut(), image);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
