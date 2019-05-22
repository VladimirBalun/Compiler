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

#include <iostream>
#include <boost/program_options.hpp>

#include "configuration.hpp"
#include "frontend/preprocessor.hpp"

int main(int argc, char** argv)
{
    try
    {
        std::string input_source_filename{};
        std::string output_exe_filename{};

        boost::program_options::options_description program_description("Program usage");
        program_description.add_options()
                ("help,h", "Show help message.")
                ("version,v", "Show version of the BCC compiler.")
                ("input,i", boost::program_options::value<std::string>(&input_source_filename), "Input source file.")
                ("output,o", boost::program_options::value<std::string>(&output_exe_filename), "Output executable file.");

        boost::program_options::variables_map variables_map{};
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, program_description), variables_map);
        boost::program_options::notify(variables_map);

        if (variables_map.count("help"))
        {
            std::cout << program_description << std::endl;
            return EXIT_SUCCESS;
        }
        if (variables_map.count("version"))
        {
            std::cout << "BCC version: " << Configuration::VERSION << std::endl;
            return EXIT_SUCCESS;
        }
        if (input_source_filename.empty() || output_exe_filename.empty())
        {
            std::cerr << program_description << std::endl;
            return EXIT_FAILURE;
        }

        Frontend::Result preprocess_result{};
        Frontend::IPreprocessor<Frontend::Preprocessor> preprocessor = Frontend::Preprocessor{};
        const Frontend::AST ast = preprocessor.process(input_source_filename, preprocess_result);
        std::cout << preprocess_result.getMessage() << std::endl;

        // TODO: need to add processing of the preprocess result

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Compilation is failure. Unknown error" << std::endl;
        return EXIT_FAILURE;
    }
}