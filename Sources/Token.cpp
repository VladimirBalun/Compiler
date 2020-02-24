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

#include "Token.hpp"

#pragma region Token

Token::Token(Tag tag)
    : m_tag(tag)
{
}

bool Token::isUnknown() const noexcept
{
    return m_tag == Tag::UNKNOWN;
}

bool Token::isNumber() const noexcept
{
    return m_tag == Tag::NUMBER;
}

bool Token::isWord() const noexcept
{
    return m_tag == Tag::WORD;
}

#pragma endregion Token

#pragma region NumberToken

NumberToken::NumberToken(Tag tag, int value) noexcept
    : Token(tag), m_value(value)
{
}

void NumberToken::setValue(int value) noexcept
{
    m_value = value;
}

int NumberToken::getValue() const noexcept
{
    return m_value;
}

#pragma endregion NumberToken

#pragma region WordToken

WordToken::WordToken(Tag tag, std::string value)
    : Token(tag), m_value(std::move(value))
{
}

void WordToken::setValue(std::string value)
{
    m_value = std::move(value);
}

std::string_view WordToken::getValue() const noexcept
{
    return m_value;
}

#pragma endregion WordToken
