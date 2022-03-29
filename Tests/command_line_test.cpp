#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../Command_line/CommandLine.h"

TEST(Command_line, check_paths) {
    char* file_name = strdup("image_processor");
    char* path1 = strdup("example.bmp");
    char* path2 = strdup("new_example.bmp");
    char* argv[3] = {file_name, path1, path2};
    CommandLine command_line(3, argv);
    ASSERT_EQ(std::string(command_line.GetFileIn()), std::string(path1));
    ASSERT_EQ(std::string(command_line.GetFileOut()), std::string(path2));
    delete file_name;
    delete path1;
    delete path2;
}

TEST(Command_line, check_filters) {
    char* file_name = strdup("image_processor");
    char* path1 = strdup("example.bmp");
    char* path2 = strdup("new_example.bmp");
    char* name_filter_1 = strdup("-a");
    char* filter_1_par1 = strdup("1");
    char* filter_1_par2 = strdup("value2");
    char* name_filter_2 = strdup("-b");
    char* filter_2_par1 = strdup("1");
    char* filter_2_par2 = strdup("value2");
    char* argv[9] = {file_name,     path1,         path2,         name_filter_1, filter_1_par1,
                     filter_1_par2, name_filter_2, filter_2_par1, filter_2_par2};
    CommandLine command_line(9, argv);
    auto filters = command_line.GetFilters();
    ASSERT_EQ(std::string(filters[0].name), "a");
    ASSERT_EQ(std::string(filters[0].parameters[0]), std::string(filter_1_par1));
    ASSERT_EQ(std::string(filters[0].parameters[1]), std::string(filter_1_par2));
    ASSERT_EQ(std::string(filters[1].name), "b");
    ASSERT_EQ(std::string(filters[1].parameters[0]), std::string(filter_2_par1));
    ASSERT_EQ(std::string(filters[1].parameters[1]), std::string(filter_2_par2));
    delete file_name;
    delete path1;
    delete path2;
    delete name_filter_1;
    delete name_filter_2;
    delete filter_1_par1;
    delete filter_1_par2;
    delete filter_2_par1;
    delete filter_2_par2;
}

TEST(Command_line, wrong_filter_name) {
    char* file_name = strdup("image_processor");
    char* path1 = strdup("example.bmp");
    char* path2 = strdup("new_example.bmp");
    char* name_filter_1 = strdup("a");
    char* argv[4] = {file_name, path1, path2, name_filter_1};
    try {
        CommandLine command_line(4, argv);
        FAIL();
    } catch (std::domain_error& e) {
        SUCCEED();
    }
    delete file_name;
    delete path1;
    delete path2;
    delete name_filter_1;
}

TEST(Command_line, wrong_filter_name_2) {
    char* file_name = strdup("image_processor");
    char* path1 = strdup("example.bmp");
    char* path2 = strdup("new_example.bmp");
    char* name_filter_1 = strdup("a");
    char* name_filter_2 = strdup("-b");
    char* argv[5] = {file_name, path1, path2, name_filter_1, name_filter_2};
    try {
        CommandLine command_line(5, argv);
        FAIL();
    } catch (std::domain_error& e) {
        SUCCEED();
    }
    delete file_name;
    delete path1;
    delete path2;
    delete name_filter_1;
    delete name_filter_2;
}
