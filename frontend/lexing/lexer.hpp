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

#include <vector>
#include <string>
#include <variant>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include "token.hpp"
#include "../result.hpp"

namespace Frontend { namespace Lexing {

    // Machine state
    class Lexer
    {
    public:
        explicit Lexer(const std::string_view& data) noexcept
            : m_lexer_state_machine(data) {}
        std::vector<std::variant<AVAILABLE_TOKENS>> process(Result& lexing_result) noexcept;
    private:

        struct FoundLetterEvent : boost::statechart::event<FoundLetterEvent> {};
        struct FoundNumberEvent : boost::statechart::event<FoundNumberEvent> {};
        struct FoundUnknownSymbolEvent : boost::statechart::event<FoundUnknownSymbolEvent> {};

        struct LetterState;
        struct NumberState;
        struct UnknownState;

        struct LexerSM : boost::statechart::state_machine<LexerSM, UnknownState>
        {
            explicit LexerSM(const std::string_view& data) noexcept
                : m_data(data), m_start_iterator(begin(data)), m_end_iterator(begin(data)) {}
            void setStartIterator(std::string_view::const_iterator iterator) noexcept;
            void setEndIterator(std::string_view::const_iterator iterator) noexcept;
            void addToken(std::variant<AVAILABLE_TOKENS>&& token) noexcept;
            const std::string_view& getData() const noexcept;
            std::string_view::const_iterator getStartIterator() const noexcept;
            std::string_view::const_iterator getEndIterator() const noexcept;
            std::vector<std::variant<AVAILABLE_TOKENS>> getTokens() const noexcept;
        private:
            const std::string_view& m_data;
            std::string_view::const_iterator m_start_iterator{};
            std::string_view::const_iterator m_end_iterator{};
            std::vector<std::variant<AVAILABLE_TOKENS>> m_tokens{};
        };

        struct LetterState : boost::statechart::simple_state<LetterState, LexerSM>
        {
            using reactions = boost::mpl::list<
                boost::statechart::custom_reaction<FoundLetterEvent>,
                boost::statechart::custom_reaction<FoundNumberEvent>,
                boost::statechart::custom_reaction<FoundUnknownSymbolEvent>>;

            boost::statechart::result react(const FoundLetterEvent& event);
            boost::statechart::result react(const FoundNumberEvent& event);
            boost::statechart::result react(const FoundUnknownSymbolEvent& event);
        };

        struct NumberState : boost::statechart::simple_state<NumberState, LexerSM>
        {
            using reactions = boost::mpl::list<
                boost::statechart::custom_reaction<FoundLetterEvent>,
                boost::statechart::custom_reaction<FoundNumberEvent>,
                boost::statechart::custom_reaction<FoundUnknownSymbolEvent>>;

            boost::statechart::result react(const FoundLetterEvent& event);
            boost::statechart::result react(const FoundNumberEvent& event);
            boost::statechart::result react(const FoundUnknownSymbolEvent& event);
        };

        struct UnknownState : boost::statechart::simple_state<UnknownState, LexerSM>
        {
            using reactions = boost::mpl::list<
                boost::statechart::custom_reaction<FoundLetterEvent>,
                boost::statechart::custom_reaction<FoundNumberEvent>,
                boost::statechart::custom_reaction<FoundUnknownSymbolEvent>>;

            boost::statechart::result react(const FoundLetterEvent& event);
            boost::statechart::result react(const FoundNumberEvent& event);
            boost::statechart::result react(const FoundUnknownSymbolEvent& event);
        };

    private:
        LexerSM m_lexer_state_machine;
    };

}}
