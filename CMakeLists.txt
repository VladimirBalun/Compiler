cmake_minimum_required(VERSION 3.10)

project(Compiler)

find_package(Boost COMPONENTS iostreams program_options system filesystem REQUIRED)

file (GLOB_RECURSE SOURCES "Sources/*.cpp" "Sources/*.hpp")

foreach (FILE ${SOURCES})
    get_filename_component (PARENT_DIR "${FILE}" DIRECTORY)
    string (REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string (REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set (GROUP "${GROUP}")
    elseif ("${FILE}" MATCHES ".*\\.hpp")
       set (GROUP "${GROUP}")
    endif ()

    source_group ("${GROUP}" FILES "${FILE}")
endforeach ()

set(CMAKE_CXX_STANDARD 17)

if(Boost_FOUND)
    add_executable (${PROJECT_NAME} ${SOURCES})
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
endif()
