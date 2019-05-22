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

namespace Frontend {

    class Result
    {
    public:

        enum class Code
        {
            OK = 0,
            INTERNAL_ERROR,
            SOURCE_FILE_NOT_READ,
            INCORRECT_IDENTIFIER,
            UNKNOWN
        };

    public:
        Result() noexcept = default;
        explicit Result(Result::Code code) noexcept
            : m_result_code(code) {}
        Result(Result::Code code, std::string cause) noexcept
                : m_result_code(code), m_cause(std::move(cause)) {}
        void setCode(Code code) noexcept;
        void setCause(const std::string& cause) noexcept;
        Code getCode() const noexcept;
        std::string getMessage() const noexcept;
    private:
        std::string m_cause{};
        Code m_result_code = Code::UNKNOWN;
    };

}
