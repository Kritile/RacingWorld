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

#include "GameWorld.h"
#include "../Utils/Ping.hpp"

namespace Graphics {

    class Scene 
    {
    public:
        explicit Scene(HDC& windowContext, GLint sceneWidth, GLint sceneHeight)
            : _ping(Ping::getInstance()), _windowContext(windowContext), _sceneWidth(sceneWidth), _sceneHeight(sceneHeight) {}
        GLvoid initScene();
        GLvoid renderScene();
        GLvoid updateScene();
    private:
        Ping& _ping;
        HDC& _windowContext;
        GLint _sceneWidth;
        GLint _sceneHeight;
        GameWorld _gameWorld;
    };

}
