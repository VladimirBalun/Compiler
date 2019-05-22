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

#include "lexer.hpp"

#include <iostream>
#include <algorithm>
#include <boost/lexical_cast.hpp>

std::vector<std::variant<AVAILABLE_TOKENS>> Frontend::Lexing::Lexer::process(Result& lexing_result) noexcept
{
    try
    {
        m_lexer_state_machine.initiate();
        const std::string_view& data = m_lexer_state_machine.getData();
        std::cout << data << std::endl;
        for (auto it = begin(data); it != end(data); ++it)
        {
            if (std::isalpha(*it))
            {
                m_lexer_state_machine.process_event(FoundLetterEvent{});
            }
            else if (std::isdigit(*it))
            {
                m_lexer_state_machine.process_event(FoundNumberEvent{});
            }
            else
            {
                m_lexer_state_machine.process_event(FoundUnknownSymbolEvent{});
            }
        }

        lexing_result.setCode(Result::Code::OK);
    }
    catch (const std::range_error& e)
    {
        lexing_result.setCode(Result::Code::INTERNAL_ERROR);
    }
    catch (const std::logic_error& e)
    {
        lexing_result.setCause(e.what());
        lexing_result.setCode(Result::Code::INCORRECT_IDENTIFIER);
    }

    return m_lexer_state_machine.getTokens();
}

void Frontend::Lexing::Lexer::LexerSM::setStartIterator(std::string_view::const_iterator iterator) noexcept
{
    m_start_iterator = iterator;
}

void Frontend::Lexing::Lexer::LexerSM::setEndIterator(std::string_view::const_iterator iterator) noexcept
{
    m_end_iterator = iterator;
}

void Frontend::Lexing::Lexer::LexerSM::addToken(std::variant<AVAILABLE_TOKENS>&& token) noexcept
{
    m_tokens.push_back(std::move(token));
}

const std::string_view& Frontend::Lexing::Lexer::LexerSM::getData() const noexcept
{
    return m_data;
}

std::string_view::const_iterator Frontend::Lexing::Lexer::LexerSM::getStartIterator() const noexcept
{
    return m_start_iterator;
}

std::string_view::const_iterator Frontend::Lexing::Lexer::LexerSM::getEndIterator() const noexcept
{
    return m_end_iterator;
}

std::vector<std::variant<AVAILABLE_TOKENS>> Frontend::Lexing::Lexer::LexerSM::getTokens() const noexcept
{
    return m_tokens;
}

boost::statechart::result Frontend::Lexing::Lexer::LetterState::react(const FoundLetterEvent& event)
{
    auto& lexer_sm = context<LexerSM>();
    const auto end_iterator = lexer_sm.getEndIterator();
    lexer_sm.setEndIterator(end_iterator + 1);
    return transit<LetterState>();
}

boost::statechart::result Frontend::Lexing::Lexer::LetterState::react(const FoundNumberEvent& event)
{
    const auto end_iterator = context<LexerSM>().getEndIterator();
    context<LexerSM>().setEndIterator(end_iterator + 1);
    return transit<LetterState>();
}

boost::statechart::result Frontend::Lexing::Lexer::LetterState::react(const FoundUnknownSymbolEvent& event)
{
    auto& lexer_sm = context<LexerSM>();
    const auto start_iterator = lexer_sm.getStartIterator();
    const auto end_iterator = lexer_sm.getEndIterator();
    const std::string word(start_iterator, end_iterator - start_iterator);
    lexer_sm.addToken(std::variant<AVAILABLE_TOKENS>(Tokens::Token<std::string>(word)));
    lexer_sm.setStartIterator(end_iterator);
    lexer_sm.setEndIterator(end_iterator + 1);
    return transit<UnknownState>();
}

boost::statechart::result Frontend::Lexing::Lexer::NumberState::react(const FoundLetterEvent& event)
{
    auto& lexer_sm = context<LexerSM>();
    const auto start_iterator = lexer_sm.getStartIterator();
    const auto end_iterator = lexer_sm.getEndIterator();
    throw std::logic_error("incorrect word '" + std::string(start_iterator, end_iterator - start_iterator + 1) + " '");
}

boost::statechart::result Frontend::Lexing::Lexer::NumberState::react(const FoundNumberEvent& event)
{
    auto& lexer_sm = context<LexerSM>();
    const auto end_iterator = lexer_sm.getEndIterator();
    lexer_sm.setEndIterator(end_iterator + 1);
    return transit<NumberState>();
}

boost::statechart::result Frontend::Lexing::Lexer::NumberState::react(const FoundUnknownSymbolEvent& event)
{
    auto& lexer_sm = context<LexerSM>();
    const auto start_iterator = lexer_sm.getStartIterator();
    const auto end_iterator = lexer_sm.getEndIterator();

    try
    {
        const int number = boost::lexical_cast<int>(start_iterator, end_iterator - start_iterator);
        lexer_sm.addToken(std::variant<AVAILABLE_TOKENS>(Tokens::Token<int>(number)));
        lexer_sm.setStartIterator(end_iterator);
        lexer_sm.setEndIterator(end_iterator + 1);
        return transit<UnknownState>();
    }
    catch (const boost::bad_lexical_cast& e)
    {
        throw std::logic_error("incorrect number '" + std::string(start_iterator, end_iterator - start_iterator + 1) + " '");
    }
}

boost::statechart::result Frontend::Lexing::Lexer::UnknownState::react(const FoundLetterEvent& event)
{
    auto& lexer_sm = context<LexerSM>();
    const auto end_iterator = lexer_sm.getEndIterator();
    lexer_sm.setStartIterator(end_iterator);
    lexer_sm.setEndIterator(end_iterator + 1);
    return transit<LetterState>();
}

boost::statechart::result Frontend::Lexing::Lexer::UnknownState::react(const FoundNumberEvent& event)
{
    auto& lexer_sm = context<LexerSM>();
    const auto end_iterator = lexer_sm.getEndIterator();
    lexer_sm.setStartIterator(end_iterator);
    lexer_sm.setEndIterator(end_iterator + 1);
    return transit<NumberState>();
}

boost::statechart::result Frontend::Lexing::Lexer::UnknownState::react(const FoundUnknownSymbolEvent& event)
{
    auto& lexer_sm = context<LexerSM>();
    const auto end_iterator = lexer_sm.getEndIterator();
    lexer_sm.setStartIterator(end_iterator);
    lexer_sm.setEndIterator(end_iterator + 1);
    return transit<UnknownState>();
}
