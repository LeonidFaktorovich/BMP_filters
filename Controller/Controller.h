#pragma once
#include <string>

#include "../Command_line/CommandLine.h"
#include "../Filters/Filters.h"
#include "../Image/Image.h"

class FilterController {
public:
    FilterController(Image* image, const std::vector<CommandLine::DataOfFilter>& filters);
    void IsCorrectFilters();
    void DoFilters();

private:
    void ValidateNumberOfArgs(const std::string& name_of_filter, int expected_args, int given_args);
    Image* image_;
    const std::vector<CommandLine::DataOfFilter>& filters_;
    std::vector<Filter*> filters_to_run_ = {};
};