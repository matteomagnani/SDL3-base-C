cmake_minimum_required(VERSION 3.16)
project(SDL3_TEST C)

# 1. Set C Standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2. Tell CMake where to find Homebrew on macOS
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

# 3. Add your source files
# It is good practice to include the .h file here so IDEs like VS Code 
# or Xcode can "see" it and provide better autocomplete.
add_executable(SDL3_TEST
        main.c
)

# 4. EXPLICITLY ADD INCLUDE DIRECTORIES
# Sometimes the target link doesn't propagate headers correctly on macOS
target_include_directories(SDL3_TEST PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "/opt/homebrew/include" # Add the Homebrew root include
)

# 5. Link everything
target_link_libraries(SDL3_TEST PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)

# ============================================
# ADD ADDRESSSANITIZER (Memory Leak Detection)
# ============================================
if(CMAKE_BUILD_TYPE MATCHES Debug OR NOT CMAKE_BUILD_TYPE)
    target_compile_options(SDL3_TEST PRIVATE -fsanitize=address -g -O1)
    target_link_options(SDL3_TEST PRIVATE -fsanitize=address)
    message(STATUS "AddressSanitizer enabled")
endif()

# 6. Copy Assets to Build Folder
#add_custom_target(copy_assets ALL
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/assets
#        ${CMAKE_BINARY_DIR}/assets
#        COMMENT "Copying assets to build directory"
#)