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

#include "Vector2.h"

template <class Type>
size_t Math::Vector2<Type>::getLength() const noexcept
{
    return sqrt(x*x + y*y);
}

template <class Type>
void Math::Vector2<Type>::normalize() noexcept
{
    const size_t length = getLength();
    if (length != 0)
    {
        x /= length;
        y /= length;
    }
}

template <class Type>
void Math::Vector2<Type>::add(const Vector2& other) noexcept
{
    x += other.x;
    y += other.y;
}

template <class Type>
void Math::Vector2<Type>::sub(const Vector2& other) noexcept
{
    x -= other.x;
    y -= other.y;
}

template <class Type>
void Math::Vector2<Type>::mul(Type scalar) noexcept
{
    x *= scalar;
    y *= scalar;
}
