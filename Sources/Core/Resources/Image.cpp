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

#include "PrecompiledHeader.hpp"
#include "Image.hpp"

#include <boost/filesystem/convenience.hpp>
#include <SOIL.h>

#include "Helpers/Debug.hpp"
#include "Loaders/ImageLoader.hpp"

void Core::Resources::Image::setWidth(std::uint16_t width) noexcept
{
    m_width = width;
}

void Core::Resources::Image::setHeight(std::uint16_t height) noexcept
{
    m_height = height;
}

void Core::Resources::Image::setData(unsigned char* data) noexcept
{
    m_data = data;
}

std::uint16_t Core::Resources::Image::getWidth() const noexcept
{
    return m_width;
}

std::uint16_t Core::Resources::Image::getHeight() const noexcept
{
    return m_height;
}

const unsigned char* Core::Resources::Image::getData() const noexcept
{
    return m_data;
}

bool Core::Resources::Image::load(std::string_view image_path) noexcept
{
    return Loaders::ImageLoader::load(*this, image_path);
}

Core::Resources::Image::~Image()
{
    SOIL_free_image_data(m_data);
}
