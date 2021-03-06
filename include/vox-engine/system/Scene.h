//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_SCENE_H
#define VOXENGINE_SCENE_H

#include "vox-engine/system/Display.h"
#include "vox-engine/system/Entity.h"
#include "vox-engine/component/Mesh.h"

class Scene {
public:
    virtual void Load() = 0;
    virtual void OnUnload();
    void unload();

    Entity *instantiate(std::string name);
    Entity *instantiate(std::string name, DrawFunction drawFunction);
    void destroy(Entity *go);
    void removeFromList(Entity *go);
    Entity *getObjectByName(std::string name);
    std::vector<Entity *> &getEntities();
private:
    std::vector<Entity *> _entityList;
    void addToList(Entity *go);
};


#endif //VOXENGINE_SCENE_H
