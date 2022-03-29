#pragma once
#include "../Command_line/CommandLine.h"
#include "../Image/Image.h"

Image ReadImageFromFile(char* path_to_file, FileFormat file_format);

Image ReaderBMP(char* path_to_file);
