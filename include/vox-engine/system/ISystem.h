//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_ISYSTEM_H
#define VOXENGINE_ISYSTEM_H

#include "vox-engine/core/Config.h"

class ISystem {
public:
    virtual void init(Config::Profile profile) {}
    virtual void start() = 0;
    virtual void reset() {}
    virtual void destroy() = 0;
};

#endif //VOXENGINE_ISYSTEM_H
