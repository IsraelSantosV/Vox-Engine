//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_APPLICATION_H
#define VOXENGINE_APPLICATION_H

#include <string>
#include <map>
#include <vector>

#include "../system/Display.h"
#include "../system/InputManager.h"
#include "../util/Profiler.h"
#include "Config.h"

#include "../system/ISystem.h"
#include "../util/Time.h"
#include "../../include/vox-engine/core/ApplicationVersion.h"
#include "../system/SceneManager.h"
#include "../system/Logic.h"
#include "../system/LightManager.h"

class Application {
public:
    static const double FIXED_TIME_INTERVAL;

    void init();
    void start();
    void reset();
    void run();
    void destroy();

    static bool isRunning() { return _isRunning; }
    static void stop();

private:
    Time *_time;
    Display *_display;
    InputManager *_inputManager;
    SceneManager *_sceneManager;
    Logic *_logic;
    LightManager *_lighting;

    Profiler *_profiler;
    Config *_config;
    Logger *_logger;

    std::vector<ISystem *> _systems;

    double _accumulatedTime, _newTime, _lastTime;

    static bool _isRunning;
};


#endif //VOXENGINE_APPLICATION_H
