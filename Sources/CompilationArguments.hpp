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

#pragma once

#include <string>

#include "Aliases.hpp"

class CompilationArguments
{
public:
    CompilationArguments();
    bool parse(int argc, char** argv);
    std::string getUsageInformation() const;
    std::string_view getInputSourceFilename() const noexcept;
    std::string_view getOutoutExecutableFilename() const noexcept;
private:
    bool isValidCompilationArguments(const bpo::variables_map& variables_map) const noexcept;
private:
    std::string m_input_source_filename;
    std::string m_output_executable_filename;
    bpo::options_description m_program_description;
};
