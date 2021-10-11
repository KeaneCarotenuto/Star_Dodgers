cmake_minimum_required(VERSION 3.0.0)
project(Star_Dodgers VERSION 0.1.0)

include(CTest)
enable_testing()

# Windows specific config
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

# Find SFML shared libraries
find_package(SFML 2.5.1 COMPONENTS graphics system window)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(Star_Dodgers ${SOURCES})
link_directories(Star_Dodgers SFML-2.5.1/lib)
target_link_libraries(Star_Dodgers sfml-graphics sfml-window sfml-system )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
