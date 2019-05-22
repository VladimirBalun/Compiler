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

#include <type_traits>

namespace Tools {

    template<typename T, typename... Rest>
    struct is_any : std::false_type {};

    template<typename T, typename First>
    struct is_any<T, First> : std::is_same<T, First> {};

    template<typename T, typename First, typename... Rest>
    struct is_any<T, First, Rest...>
            : std::integral_constant<bool, std::is_same<T, First>::value || is_any<T, Rest...>::value>
    {};

}