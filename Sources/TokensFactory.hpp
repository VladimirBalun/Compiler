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

#include <memory>
#include <string>
#include <type_traits>

#include "Token.hpp"

class TokensFactory
{
public:
    template<typename T>
    std::shared_ptr<Token> create(T&& value);
    template<typename T>
    void create(std::shared_ptr<Token>& token, T&& value);
};

template<typename T>
std::shared_ptr<Token> TokensFactory::create(T&& value)
{
    if constexpr (std::is_same_v<T, int>)
    {
        return std::make_shared<NumberToken>(Token::Tag::NUMBER, value);
    }
    if constexpr (std::is_same_v<T, std::string>)
    {
        return std::make_shared<NumberToken>(Token::Tag::WORD, std::move(value));
    }
    
    return nullptr;
}

template<typename T>
void TokensFactory::create(std::shared_ptr<Token>& token, T&& value)
{
    std::shared_ptr<Token> temp_token = create(std::forward<T>(value));
    token.swap(temp_token);
}
