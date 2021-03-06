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
#include <cstdint>

#include "IManager.hpp"
#include "../Helpers/Holders/Singleton.hpp"

#ifndef g_configuration_manager
    #define g_configuration_manager Core::Managers::ConfigurationManager::getInstance()
#endif // g_configuration_manager

namespace Core::Managers 
{

    class ConfigurationManager : public IManager<ConfigurationManager>, public Helpers::Holders::Singleton<ConfigurationManager>
    {
    public:
        void initialize();
        std::string getCurrentLanguage() const noexcept;
        std::string_view getMapsPath() const noexcept;
        std::string_view getModelsPath() const noexcept;
        std::string_view getShadersPath() const noexcept;
        std::string_view getResourcesPath() const noexcept;
        std::string_view getLocalesConfigurationFilename() const noexcept;
        std::string_view getPlayerConfigurationFilename() const noexcept;
        std::string_view getResourcesConfigurationFilename() const noexcept;
    private:
        std::string m_current_language{};
        std::string m_player_file_configuration_path{};
        std::string m_locales_file_configuration_path{};
        std::string m_resources_file_configuration_path{};
    };

}
