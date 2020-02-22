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
    enum class GrammarLabel
    {
        UNKNOWN = 0,
        IDENTIFIER,
        NUMBER
    };
public:
    Token() = default;
    Token(std::string value, GrammarLabel label);
    void setValue(std::string value);
    void setGrammarLabel(GrammarLabel label);
    std::string_view getValue() const noexcept;
    GrammarLabel getGrammarLabel() const noexcept;
private:
    std::string m_value;
    GrammarLabel m_grammar_label;
};
