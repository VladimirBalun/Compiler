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

#include "result.hpp"

void Frontend::Result::setCode(Code code) noexcept
{
    m_result_code = code;
}

void Frontend::Result::setCause(const std::string& cause) noexcept
{
    m_cause = cause;
}

Frontend::Result::Code Frontend::Result::getCode() const noexcept
{
    return m_result_code;
}

std::string Frontend::Result::getMessage() const noexcept
{
    std::string message{};
    const std::string error_message = "BCC error C" + std::to_string(static_cast<int>(m_result_code)) + ": ";

    switch (m_result_code)
    {
        case Code::OK:
            message.append("Preprocess finished successfully.");
            break;
        case Code::INTERNAL_ERROR:
            message.append(error_message + "Internal error, please write about it to developers.");
            break;
        case Code::SOURCE_FILE_NOT_READ:
            message.append(error_message + "Source file was not opened.");
            break;
        case Code::INCORRECT_IDENTIFIER:
            message.append(error_message + "Incorrect identifier.");
            break;
        case Code::UNKNOWN:
            message.append(error_message + "Preprocess status is unknown.");
            break;
    }

    if (!m_cause.empty())
        message.append(" More: " + m_cause);
    return message;
}
