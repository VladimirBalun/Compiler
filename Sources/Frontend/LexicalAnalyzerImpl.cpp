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

#include "LexicalAnalyzerImpl.hpp"
#include "../Token.hpp"

#include <boost/lexical_cast.hpp>

std::vector<Token::SPtr> Frontend::LexicalAnalyzer::Impl::scan(std::string_view data)
{
    std::vector<Token::SPtr> result_tokens{};
    for (auto iterator = std::begin(data); iterator != std::end(data); ++iterator)
    {
        const char current_symbol = *iterator;
        if (std::isspace(current_symbol))
        {
            ++iterator;
            continue;
        }
        
        if (std::isdigit(current_symbol))
        {
            DigitToken::SPtr token = scanDigit(iterator, data.end());
            result_tokens.push_back(std::move(token));
        }
        
        if (std::isalnum(current_symbol))
        {
            WordToken::SPtr token = scanWord(iterator, data.end());
            result_tokens.push_back(std::move(token));
        }
    }
    
    return result_tokens;
}

WordToken::SPtr Frontend::LexicalAnalyzer::Impl::scanWord(std::string_view::iterator& iterator, std::string_view::iterator end_data)
{
    std::string_view::iterator start_iterator = iterator;
    while ( (iterator != end_data) && ( (std::isalnum(*iterator)) || (std::isdigit(*iterator)) ) )
    {
        ++iterator;
    }
    
    std::string target_value(start_iterator, iterator);
    return std::make_shared<WordToken>(std::move(target_value));
}

DigitToken::SPtr Frontend::LexicalAnalyzer::Impl::scanDigit(std::string_view::iterator& iterator, std::string_view::iterator end_data)
{
    std::string_view::iterator start_iterator = iterator;
    while ( (iterator != end_data) && (std::isdigit(*iterator)) )
    {
        ++iterator;
    }
    
    const std::string target_value(start_iterator, iterator);
    ssize_t target_digit_value = boost::lexical_cast<ssize_t>(target_value);
    return std::make_shared<DigitToken>(target_digit_value);
}
