cmake_minimum_required(VERSION 3.10)

project(bcc)

find_package(Boost COMPONENTS iostreams program_options system filesystem REQUIRED)

set(CMAKE_CXX_STANDARD 17)

if(Boost_FOUND)
    add_executable(${CMAKE_PROJECT_NAME} main.cpp configuration.hpp frontend/ipreprocessor.hpp frontend/result.hpp frontend/result.cpp frontend/preprocessor.hpp frontend/preprocessor.cpp frontend/lexing/keywords.hpp frontend/lexing/lexems.hpp frontend/ast.hpp frontend/lexing/lexer.hpp frontend/lexing/token.hpp frontend/ast.cpp frontend/lexing/lexer.cpp frontend/parsing/parser.hpp frontend/parsing/parser.cpp tools/metafunctions.h frontend/lexing/keywords.cpp)
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
endif()
