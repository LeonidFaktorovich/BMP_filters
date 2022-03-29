cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        ../image_processor.cpp
        "../Command_line/CommandLine.cpp"
        ../Filters/Filters.h
        "../Command_line/Help.cpp"
        ../Image/Image.cpp
        ../Image/ImageStructures.cpp
        ../Image/Pixels.cpp
        "../File_Interaction/Reader.cpp"
        "../File_Interaction/Writer.cpp"
        ../Controller/Controller.cpp
        ../Controller/Controller.h
        ../Filters/FilterWithCoefficients.cpp
        ../Filters/FilterWithCoefficients.h
        ../Filters/Grayscale.cpp
        ../Filters/Grayscale.h
        ../Filters/Negative.cpp
        ../Filters/Negative.h
        ../Filters/FilterWithMatrix.cpp
        ../Filters/FilterWithMatrix.h
        ../Filters/EdgeDetection.cpp
        ../Filters/EdgeDetection.h
        ../Filters/Sharpening.cpp
        ../Filters/Sharpening.h
        ../Filters/FilterWithAffineMatrix.cpp
        ../Filters/FilterWithAffineMatrix.h
        ../Filters/Reflection.cpp
        ../Filters/Reflection.h
        ../Filters/Rotation.cpp
        ../Filters/Rotation.h
        ../Filters/GaussianBlur.cpp
        ../Filters/GaussianBlur.h
        ../Filters/Crystallize.cpp
        ../Filters/Crystallize.h
        ../Filters/Crop.cpp
        ../Filters/Crop.h)

enable_testing()

include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929
        )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_image_processor
        ../Tests/filter_test.cpp
        ../Tests/command_line_test.cpp
        ../Tests/pixels_test.cpp
        ../Tests/read_file_test.cpp
        ../Tests/image_test.cpp
        ../Tests/controller_test.cpp)

add_library(library_for_testing
        "../Command_line/CommandLine.cpp"
        ../Filters/Filters.h
        "../Command_line/Help.cpp"
        ../Image/Image.cpp
        ../Image/ImageStructures.cpp
        ../Image/Pixels.cpp
        "../File_Interaction/Reader.cpp"
        "../File_Interaction/Writer.cpp"
        ../Controller/Controller.cpp
        ../Controller/Controller.h
        ../Filters/FilterWithCoefficients.cpp
        ../Filters/FilterWithCoefficients.h
        ../Filters/Grayscale.cpp
        ../Filters/Grayscale.h
        ../Filters/Negative.cpp
        ../Filters/Negative.h
        ../Filters/FilterWithMatrix.cpp
        ../Filters/FilterWithMatrix.h
        ../Filters/EdgeDetection.cpp
        ../Filters/EdgeDetection.h
        ../Filters/Sharpening.cpp
        ../Filters/Sharpening.h
        ../Filters/FilterWithAffineMatrix.cpp
        ../Filters/FilterWithAffineMatrix.h
        ../Filters/Reflection.cpp
        ../Filters/Reflection.h
        ../Filters/Rotation.cpp
        ../Filters/Rotation.h
        ../Filters/GaussianBlur.cpp
        ../Filters/GaussianBlur.h
        ../Filters/Crystallize.cpp
        ../Filters/Crystallize.h
        ../Filters/Crop.cpp
        ../Filters/Crop.h
        )

target_link_libraries(test_image_processor PUBLIC gtest_main library_for_testing)

include(GoogleTest)

gtest_discover_tests(test_image_processor)