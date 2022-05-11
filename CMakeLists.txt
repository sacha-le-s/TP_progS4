cmake_minimum_required(VERSION 3.8)

project(SimpleCpp)
add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Enable many good warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W3)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

# Set the folder where the executable is created
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Add all the files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
add_subdirectory(p6)                                  # Includes the p6 library ; this assumes that you have a folder called p6 at the same level as this CMakeLists.txt file, and that the p6 folder contains a CMakeLists.txt file
target_link_libraries(${PROJECT_NAME} PRIVATE p6::p6) # Adds the target "p6::p6" as a dependency of our target ${PROJECT_NAME}. Unfortunately the command is called target_link_libraries() even though it can be used for other things than just linking ; don't get confused! A better name would have been add_dependency()
                                                      # The name of the target "p6::p6" is up to the library authors. Check out their documentation to know how they called it!
                                                      # The "::" in the name of the library's target is not mandatory, but library authors often add it because target_link_libraries() can do many different things, and if you make a typo in the name of the target it will ignore it instead of reporting an error. It is only if you have a "::" in the name that target_link_libraries() will know that it can't be anything but a target and will raise an error if the name doesn't actually correspond to a target.
