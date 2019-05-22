/*
 * Copyright 2018 Vladimir Balun
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

#include "preprocessor.hpp"

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include "lexing/lexer.hpp"
#include "parsing/parser.hpp"

Frontend::AST Frontend::Preprocessor::process(const std::string_view& source_filename, Result& preprocess_result) noexcept
{
    const std::string source_data = readSourceFile(source_filename);
    if (source_data.empty())
    {
        preprocess_result.setCode(Result::Code::SOURCE_FILE_NOT_READ);
        const std::string full_source_filename = (boost::filesystem::current_path() / source_filename.data()).string();
        preprocess_result.setCause("file '" + full_source_filename + "' is busy or is absent.");
        return AST{};
    }

    Lexing::Lexer lexer(source_data);
    const auto tokens = lexer.process(preprocess_result);
    if (preprocess_result.getCode() != Result::Code::OK)
    {
        return AST{};
    }

    Parsing::Parser parser{};
    const AST ast = parser.process(tokens, preprocess_result);
    return ast;
}

std::string Frontend::Preprocessor::readSourceFile(const std::string_view& source_filename) const noexcept
{
    const boost::filesystem::path full_path = source_filename.data();
    if (!boost::filesystem::exists(full_path))
    {
        return "";
    }

    boost::iostreams::mapped_file mmap(full_path, boost::iostreams::mapped_file::readonly);
    if (!mmap.is_open())
    {
        return "";
    }

    const std::string source_data = mmap.const_data();
    return source_data;
}
