cmake_minimum_required(VERSION 3.8)

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

# Automatically file all source files in the src folder and its subfolders
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")
file(GLOB_RECURSE GUI_SOURCES "include/imgui_impl_sdl2.cpp" "include/imgui_impl_opengl3.cpp")

# Add source to this project's executable.
add_executable(StatView ${SOURCES} ${GUI_SOURCES} "src/Gui/Guis/HelloWorldGui.cpp")

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
  "src/Guis"
  "src/Stats"
  "src/Utility"
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
