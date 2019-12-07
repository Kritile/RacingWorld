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
#include "Renderer.hpp"

#include "Shader.hpp"
#include "SceneGraph/Node.hpp"
#include "SceneGraph/Scene.hpp"

void Core::Graphics::Renderer::draw(const SceneGraph::Scene& scene, const std::string& shader_id)
{
    SceneGraph::NodeSPtr root_node = scene.getRootNode();
    m_basic_shader = scene.getShaderByID(shader_id);
    m_basic_shader->use();
    drawNode(root_node);
}

void Core::Graphics::Renderer::drawNode(SceneGraph::NodeSPtr node)
{
    if (node->isExistChildren())
    {
        for (auto it = node->childrenBegin(); it != node->childrenEnd(); ++it)
        {
            SceneGraph::NodeSPtr child_node = *it;
            drawNode(child_node);
        }
    }

    const glm::mat4x4& transformation = node->getTransformation();
    m_basic_shader->setUniformMatrix4x4f("vs_un_model", transformation);
    m_basic_shader->setUniformi("fs_un_texture", 0);
    if (const SceneGraph::Mesh* mesh = node->getMesh())
    {
        mesh->draw();
    }
}
