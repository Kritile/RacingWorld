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
#include <vector>
#include <glm/fwd.hpp>

namespace Core { namespace Graphics {

    class Shader
    {
    public:
        Shader() noexcept = default;
        Shader(const std::string& vertex_shader_data, const std::string& fragment_shader_data) noexcept;
        void use() const noexcept;
        bool isValid() const noexcept;
        void setUniformf(const char* name, float value) const noexcept;
        void setUniformVector3f(const char* name, const glm::vec3& vector) const noexcept;
        void setUniformMatrix4x4f(const char* name, const glm::mat3& matrix) const noexcept;
        ~Shader();
    private:
        unsigned int compileShader(const std::string& shader_data, int shader_type) noexcept;
        void linkShaders(unsigned int vertex_shader, unsigned int fragment_shader) noexcept;
    private:    
        unsigned int m_program_id = 0;
    };

}}
