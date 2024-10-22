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

#include "LexicalAnalyzer.hpp"
#include "LexicalAnalyzerImpl.hpp"

Frontend::LexicalAnalyzer::LexicalAnalyzer()
    : m_pimpl(std::make_unique<Impl>())
{
}

std::vector<std::shared_ptr<Token>> Frontend::LexicalAnalyzer::scan(std::string_view data)
{
    return m_pimpl->scan(data);
}

Frontend::LexicalAnalyzer::~LexicalAnalyzer()
{
}
