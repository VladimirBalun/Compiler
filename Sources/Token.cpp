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

Token::Token(std::string value, GrammarLabel label)
    : m_value(std::move(value)), m_grammar_label(label)
{
}

void Token::setValue(std::string value)
{
    m_value = std::move(value);
}

void Token::setGrammarLabel(GrammarLabel label)
{
    m_grammar_label = label;
}

std::string_view Token::getValue() const noexcept
{
    return m_value;
}

Token::GrammarLabel Token::getGrammarLabel() const noexcept
{
    return m_grammar_label;
}
