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

#include "ModelLoader.hpp"

#include <OBJLoader.hpp>

#include "../Model.hpp"
#include "../../Managers/ResourceManager.hpp"

#define UNPACK_OBJ1_VEC2(__vector__) \
    ( (__vector__).X, (__vector__).Y )

#define UNPACK_OBJ1_VEC3(__vector__) \
    ( (__vector__).X, (__vector__).Y, (__vector__).Z )

bool Core::Resources::Loaders::OBJLoader::load(Model& model, const std::string& model_file_path) noexcept
{
    objl::Loader obj_loader{};
    const bool was_loaded = obj_loader.LoadFile(model_file_path);
    if (was_loaded)
    {
        for (const auto& imported_mesh : obj_loader.LoadedMeshes)
        {
            Model::Mesh mesh(imported_mesh.Vertices.size(), imported_mesh.Indices.size());
            for (const auto& imported_vertex : imported_mesh.Vertices)
            {
                glm::vec3 position{ UNPACK_OBJ1_VEC3(imported_vertex.Position) };
                glm::vec3 normal{ UNPACK_OBJ1_VEC3(imported_vertex.Normal) };
                glm::vec2 texture_coordinate{ UNPACK_OBJ1_VEC2(imported_vertex.TextureCoordinate) };
                mesh.emplaceVertex(position, normal, texture_coordinate);
            }
            for (const auto index : imported_mesh.Indices)
            {
                mesh.addIndex(index);
            }

            const std::string mesh_name = imported_mesh.MeshName;
            model.addMesh(mesh_name, std::move(mesh));
        }

        return true;
    }

    return false;
}
