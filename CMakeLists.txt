cmake_minimum_required(VERSION 3.8)

# Output paths
# Set the output directory for all build products
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)  # Static libraries typically go with other libraries

# Optional: If you want to apply these directories for multi-configuration generators
# like Visual Studio and Xcode, you might also need to set these for each configuration:
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/out/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/out/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/out/lib)
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# Use vcpkg toolchain file
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "Vcpkg toolchain file")
endif()

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
endif()

project("StatView")

# Automatically file all source files in the src folder and its subfolders.
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")
file(GLOB_RECURSE GUI_SOURCES "include/imgui_impl_sdl2.cpp" "include/imgui_impl_opengl3.cpp" "include/tinyfiledialogs.c")

# Add source to this project's executable.
add_executable(StatView ${SOURCES} ${GUI_SOURCES})

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StatView PROPERTY CXX_STANDARD 20)
endif()

# Find packages using vcpkg
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Include glm headers
find_path(GLM_INCLUDE_DIRS "glm/glm.hpp")

# Include directories
target_include_directories(StatView PRIVATE 
  ${GLM_INCLUDE_DIRS}
  "include"
  "src"
  "src/Gui"
  "src/Gui/Guis"
  "src/Gui/Guis/PerformanceGui"
  "src/Gui/ImGui"
  "src/Stats"
  "src/Stats/Captured"
  "src/Stats/Parsing"
  "src/Utility"
  "src/Utility/File"
  "src/Utility/Progress"
  "src/Utility/Update"
  "src/Utility/Update/Implementations"
)

# Link libraries to the executable
target_link_libraries(StatView PRIVATE 
    OpenGL::GL
    GLEW::GLEW
    imgui::imgui
    implot::implot
    SDL2::SDL2
    SDL2::SDL2main
    nlohmann_json::nlohmann_json
)

# Copy resources folder
add_custom_command(
    TARGET StatView POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying resources to output directory..."
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "${CMAKE_BINARY_DIR}/out/bin/resources"
)

# Print paths
message(STATUS "Runtime output path: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Library output path: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "Achieve output path: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")