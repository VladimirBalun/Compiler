/*
 * Copyright 2020 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CompilationArguments.hpp"

#include <sstream>

CompilationArguments::CompilationArguments()
    : m_program_description("Program usage")
{
    m_program_description.add_options()
        ("help,h", "Show help message.")
        ("input,i", bpo::value<std::string>(&m_input_source_filename), "Input source file.")
        ("output,o", bpo::value<std::string>(&m_output_executable_filename), "Output executable file.");
}

bool CompilationArguments::parse(int argc, char** argv)
{
    bpo::variables_map variables_map{};
    bpo::store(bpo::parse_command_line(argc, argv, m_program_description), variables_map);
    bpo::notify(variables_map);
    return isValidCompilationArguments(variables_map);
}

bool CompilationArguments::isValidCompilationArguments(const bpo::variables_map& variables_map) const noexcept
{
    return (!variables_map.count("help"))
        && (!m_input_source_filename.empty())
        && (!m_output_executable_filename.empty());
}

std::string CompilationArguments::getUsageInformation() const
{
    std::stringstream stream{};
    stream << m_program_description;
    return stream.str();
}

std::string_view CompilationArguments::getInputSourceFilename() const noexcept
{
    return m_input_source_filename;
}

std::string_view CompilationArguments::getOutoutExecutableFilename() const noexcept
{
    return m_output_executable_filename;
}
