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

class Token
{
public:
    enum class Tag
    {
        UNKNOWN = 0,
        NUMBER,
        WORD
    };
public:
    Token() = default;
    explicit Token(Tag tag);
    bool isUnknown() const noexcept;
    bool isNumber() const noexcept;
    bool isWord() const noexcept;
    virtual ~Token() = default;
private:
    Tag m_tag = Tag::UNKNOWN;
};

class NumberToken : public Token
{
public:
    NumberToken() noexcept = default;
    NumberToken(Tag tag, int value) noexcept;
    void setValue(int value) noexcept;
    int getValue() const noexcept;
private:
    int m_value = 0;
};

class WordToken : public Token
{
public:
    WordToken() = default;
    WordToken(Tag tag, std::string value);
    void setValue(std::string value);
    std::string_view getValue() const noexcept;
private:
    std::string m_value{};
};
