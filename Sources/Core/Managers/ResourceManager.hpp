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

#include <optional>
#include <boost/property_tree/ptree.hpp>

#include "IManager.hpp"
#include "../ManagersFWD.hpp"
#include "../Resources.hpp"
#include "../Resources/IResource.hpp"
#include "../Resources/ResourceTypes.hpp"
#include "../Helpers/Debug.hpp"
#include "../Helpers/Holders/Singleton.hpp"

#ifndef g_resource_manager
    #define g_resource_manager Core::Managers::ResourceManager::getInstance()
#endif // g_resource_manager

namespace Core::Managers
{

    class ResourceManager : public IManager<ResourceManager>, public Helpers::Holders::Singleton<ResourceManager>
    {
        using resources_map_t = std::unordered_map<std::string, Resources::IResourceSPtr>;
    public:
        void initialize();
        template<typename T>
        std::shared_ptr<T> getResource(const std::string& resource_id) const noexcept;
        template<typename T>
        std::optional<T> loadResource(const std::string& resource_path) const;
        template<typename T>
        void loadResource(const std::string& resource_id, std::shared_ptr<T> resource) noexcept;
        template<typename T>
        bool isExistsResource(const std::string& resource_id) noexcept;
    private:
        template<typename T>
        void loadSection(const boost::property_tree::ptree& section) noexcept;
        template<typename T>
        void loadResource(const std::string& resource_id, std::string_view resource_path) noexcept;
    private:
        std::array<resources_map_t, TO_SIZE_T(Resources::ResourceType::COUNT_TYPES)> m_resources{};
    };

    template<typename T>
    std::shared_ptr<T> ResourceManager::getResource(const std::string& resource_id) const noexcept
    {
        constexpr Resources::ResourceType resource_type = Resources::getResourceType<T>();
        if (resource_type != Resources::ResourceType::UNKNOWN)
        {
            const auto resource_type_index = TO_SIZE_T(resource_type);
            const resources_map_t& resources_for_current_type = m_resources.at(resource_type_index);
            const auto it = resources_for_current_type.find(resource_id);
            if (it != end(resources_for_current_type))
            {
                return std::dynamic_pointer_cast<T>(it->second);
            }
        }

        return nullptr;
    }

    template<typename T>
    std::optional<T> ResourceManager::loadResource(const std::string& resource_path) const
    {
        std::optional<T> resource = T{};
        const bool sucessfull_result = resource->load(resource_path);
        if (!sucessfull_result)
        {
            LOG_WARNING("Resource {'" + STR(resource_path) + "'} was not loaded.");
            return std::nullopt;
        }

        return resource;
    }

    template<typename T>
    void ResourceManager::loadResource(const std::string& resource_id, std::shared_ptr<T> resource) noexcept
    {
        constexpr Resources::ResourceType resource_type = Resources::getResourceType<T>();
        if (resource_type != Resources::ResourceType::UNKNOWN)
        {
            const auto resource_type_index = TO_SIZE_T(resource_type);
            resources_map_t& resources_for_current_type = m_resources.at(resource_type_index);
            resources_for_current_type.emplace(resource_id, resource);
        }
    }

    template<typename T>
    bool ResourceManager::isExistsResource(const std::string& resource_id) noexcept
    {
        constexpr Resources::ResourceType resource_type = Resources::getResourceType<T>();
        if (resource_type != Resources::ResourceType::UNKNOWN)
        {
            const auto resource_type_index = TO_SIZE_T(resource_type);
            resources_map_t& resources_for_current_type = m_resources.at(resource_type_index);
            const auto it = resources_for_current_type.find(resource_id);
            return it != end(resources_for_current_type);
        }

        return false;
    }

    template<typename T>
    void ResourceManager::loadSection(const boost::property_tree::ptree& section) noexcept
    {
        const std::string& resources_path = STR(g_configuration_manager.getResourcesPath());
        for (const auto& data : section)
        {
            const std::string resource_id = data.first;
            const std::string resource_path = resources_path + data.second.get_value("");
            loadResource<T>(resource_id, resource_path);
        }
    }

    template<typename T>
    void ResourceManager::loadResource(const std::string& resource_id, std::string_view resource_path) noexcept
    {
        constexpr Resources::ResourceType resource_type = Resources::getResourceType<T>();
        if (resource_type != Resources::ResourceType::UNKNOWN)
        {
            const auto resource_type_index = TO_SIZE_T(resource_type);
            resources_map_t& resources_for_current_type = m_resources.at(resource_type_index);
            auto resource = std::make_shared<T>();
            if (resource->load(resource_path))
            {
                resources_for_current_type.emplace(resource_id, resource);
            }
            else
            {
                LOG_WARNING("Resource {'" + resource_id + "' : '" + STR(resource_path) + "'} was not loaded.");
            }
        }
    }

}
