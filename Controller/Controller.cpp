#include "Controller.h"

#include <iostream>
#include <string>

#include "../Filters/Crop.h"
#include "../Filters/Crystallize.h"
#include "../Filters/EdgeDetection.h"
#include "../Filters/GaussianBlur.h"
#include "../Filters/Grayscale.h"
#include "../Filters/Negative.h"
#include "../Filters/Reflection.h"
#include "../Filters/Rotation.h"
#include "../Filters/Sharpening.h"

void FilterController::ValidateNumberOfArgs(const std::string& name_of_filter, int expected_args, int given_args) {
    if (expected_args != given_args) {
        std::cerr << "Filter " << name_of_filter << " expected " << expected_args << " arguments, but was given "
                  << given_args << std::endl;
        for (auto filter : filters_to_run_) {
            delete filter;
        }
        exit(1);
    }
}

void FilterController::IsCorrectFilters() {
    unsigned int current_width = image_->GetPixels()->GetImageWidth();
    unsigned int current_height = image_->GetPixels()->GetImageHeight();
    for (const auto& filter : filters_) {
        if (std::string(filter.name) == "gs") {
            ValidateNumberOfArgs("grayscale", 0, filter.parameters.size());
            Grayscale* new_gs = new Grayscale();
            filters_to_run_.push_back(new_gs);
        } else if (std::string(filter.name) == "neg") {
            ValidateNumberOfArgs("negative", 0, filter.parameters.size());
            Negative* new_neg = new Negative();
            filters_to_run_.push_back(new_neg);
        } else if (std::string(filter.name) == "edge") {
            ValidateNumberOfArgs("edge detection", 1, filter.parameters.size());
            float threshold = std::stof(filter.parameters[0]);
            if (threshold == 0) {
                std::cerr << "Not correct value for threshold in filter sharpening" << std::endl;
                exit(1);
            }
            EdgeDetection* new_edge = new EdgeDetection(threshold);
            filters_to_run_.push_back(new_edge);
        } else if (std::string(filter.name) == "sharp") {
            ValidateNumberOfArgs("sharpening", 0, filter.parameters.size());
            Sharpening* new_sharp = new Sharpening();
            filters_to_run_.push_back(new_sharp);
        } else if (std::string(filter.name) == "ref") {
            ValidateNumberOfArgs("reflection", 0, filter.parameters.size());
            Reflection* new_ref = new Reflection(current_width);
            filters_to_run_.push_back(new_ref);

        } else if (std::string(filter.name) == "rot") {
            ValidateNumberOfArgs("rotation", 1, filter.parameters.size());
            float phi = std::stof(filter.parameters[0]);
            if (phi == 0) {
                std::cerr << "Not correct value for phi in filter rotation" << std::endl;
                exit(1);
            }
            Rotation* new_rot = new Rotation(phi, current_width, current_height);
            filters_to_run_.push_back(new_rot);
        } else if (std::string(filter.name) == "blur") {
            ValidateNumberOfArgs("gaussian blur", 1, filter.parameters.size());
            float sigma = std::stof(filter.parameters[0]);
            if (sigma == 0) {
                std::cerr << "Not correct value for sigma in filter gaussian blur" << std::endl;
                exit(1);
            }
            GaussianBlur* new_gauss = new GaussianBlur(sigma);
            filters_to_run_.push_back(new_gauss);
        } else if (std::string(filter.name) == "crystal") {
            ValidateNumberOfArgs("crystallize", 1, filter.parameters.size());
            int count = std::stoi(filter.parameters[0]);
            if (count <= 0) {
                std::cerr << "Not correct value for count in filter crystallize" << std::endl;
                exit(1);
            }
            Crystallize* new_crystal = new Crystallize(count);
            filters_to_run_.push_back(new_crystal);
        } else if (std::string(filter.name) == "crop") {
            ValidateNumberOfArgs("crop", 2, filter.parameters.size());
            int width = std::atoi(filter.parameters[0]);
            if (width <= 0) {
                std::cerr << "Not correct value for width in filter crop" << std::endl;
                exit(1);
            }
            int height = std::atoi(filter.parameters[1]);
            if (height <= 0) {
                std::cerr << "Not correct value for height in filter crop" << std::endl;
                exit(1);
            }
            Crop* new_crop = new Crop(static_cast<unsigned int>(std::atoi(filter.parameters[0])),
                                      static_cast<unsigned int>(std::atoi(filter.parameters[1])));
            filters_to_run_.push_back(new_crop);
            current_width = std::min(static_cast<unsigned int>(width), image_->GetPixels()->GetImageWidth());
            current_height = std::min(static_cast<unsigned int>(height), image_->GetPixels()->GetImageHeight());
        } else {
            std::cerr << "Filter: " << filter.name << " is not supported" << std::endl;
            exit(1);
        }
    }
}

FilterController::FilterController(Image* image, const std::vector<CommandLine::DataOfFilter>& filters)
    : image_(image), filters_(filters) {
    IsCorrectFilters();
}

void FilterController::DoFilters() {
    for (auto filter : filters_to_run_) {
        filter->DoFilter(image_);
        delete filter;
    }
}