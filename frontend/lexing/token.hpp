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

#pragma once

#include <string>

#include "../../tools/metafunctions.h"

namespace Frontend { namespace Lexing { namespace Tokens {

    #define AVAILABLE_TOKENS \
        Frontend::Lexing::Tokens::Token<int>, \
        Frontend::Lexing::Tokens::Token<char>, \
        Frontend::Lexing::Tokens::Token<std::string>

    template<typename T>
    class Token
    {
    public:

        enum class Type
        {
            LEXEM,
            NUMBER,
            WORD,
            UNKNOWN
        };

    public:
        Token() noexcept = default;
        explicit Token(const T& value) noexcept;
        T getValue() const noexcept;
        Type getType() const noexcept;
    private:
        T m_value = T{};
        Type m_type = Type::UNKNOWN;
    };

    template<typename T>
    Token<T>::Token(const T& value) noexcept
        : m_value(value)
    {
        static_assert(Tools::is_any<T, int, char, std::string>::value,
                "Incorrect value type for token, at the moment supports only 'int', 'char' and 'std::string'.");

        if (std::is_same<T, int>::value)
        {
            m_type = Type::NUMBER;
        }
        if (std::is_same<T, char>::value)
        {
            m_type = Type::LEXEM;
        }
        if (std::is_same<T, std::string>::value)
        {
            m_type = Type::WORD;
        }
    }

    template<typename T>
    T Token<T>::getValue() const noexcept
    {
        return m_value;
    }

    template<typename T>
    typename Token<T>::Type Token<T>::getType() const noexcept
    {
        return m_type;
    }

}}}
