
cmake_minimum_required(VERSION 3.20)

project(RasterGraphicsLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COMMON_SOURCES
    src/Color.cpp
    src/Image.cpp
    src/Canvas.cpp
    src/Gradient.cpp
    src/PPMExporter.cpp
    src/ImageFilter.cpp
)

# Main application
add_executable(RasterGraphicsLab
    src/main.cpp
    ${COMMON_SOURCES}
)

# Gradient tests
add_executable(GradientTest
    tests/GradientTest.cpp
    src/Color.cpp
    src/Image.cpp
    src/Gradient.cpp
    src/PPMExporter.cpp
)

# Image filter tests
add_executable(ImageFilterTest
    tests/ImageFilterTest.cpp
    src/Color.cpp
    src/Image.cpp
    src/ImageFilter.cpp
    src/PPMExporter.cpp
)

# Include directories and compiler warnings
foreach(target
    RasterGraphicsLab
    GradientTest
    ImageFilterTest
)
    target_include_directories(${target}
        PRIVATE ${PROJECT_SOURCE_DIR}/include
    )

    if(MSVC)
        target_compile_options(${target}
            PRIVATE /W4 /WX /permissive-
        )
    else()
        target_compile_options(${target}
            PRIVATE -Wall -Wextra -Werror -pedantic
        )
    endif()
endforeach()
