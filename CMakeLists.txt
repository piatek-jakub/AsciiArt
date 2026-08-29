cmake_minimum_required (VERSION 3.14)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Fixed LANGUAGES keyword syntax
project("AsciiArt" VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source and header files
set(SOURCES
    src/AsciiArt.cpp
    src/HeaderChecker.cpp
    src/ImageLoader.cpp
    src/ImageConverter.cpp
    external/stb/stb_impl.cpp
)

set(HEADERS
    include/Pixel.hpp
    include/HeaderChecker.hpp
    include/ImageLoader.hpp
    include/ImageConverter.hpp
    external/stb/stb_image.h
)

# Create the executable
add_executable(AsciiArt ${SOURCES} ${HEADERS})

# Fixes "cannot open source file": Tells compiler to search include/ and external/ for headers
target_include_directories(AsciiArt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)