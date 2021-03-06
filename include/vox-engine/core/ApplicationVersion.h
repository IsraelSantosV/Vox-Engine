//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_APPLICATIONVERSION_H
#define VOXENGINE_APPLICATIONVERSION_H

#define VOX_ENGINE_APPLICATION_NAME "VoxEngine"
#define VOX_ENGINE_VERSION_MAJOR 0
#define VOX_ENGINE_VERSION_MINOR 1
#define VOX_ENGINE_VERSION_PATCH 0
#define VOX_ENGINE_VERSION_BUILD 1000

#define TO_STR2(x) #x
#define TO_STR(x) TO_STR2(x)
#define VOX_ENGINE_VERSION (VOX_ENGINE_APPLICATION_NAME " " TO_STR(VOX_ENGINE_VERSION_MAJOR) "." TO_STR(VOX_ENGINE_VERSION_MINOR) "." TO_STR(VOX_ENGINE_VERSION_PATCH) ":" TO_STR(VOX_ENGINE_VERSION_BUILD))

#endif //VOXENGINE_APPLICATIONVERSION_H
