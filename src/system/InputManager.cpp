//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/system/InputManager.h"

std::vector<int> InputManager::_keyPress;
std::vector<int> InputManager::_keyDown;
std::vector<int> InputManager::_keyRelease;
float InputManager::_xPos = 0;
float InputManager::_yPos = 0;
float InputManager::_xPosLast = 0;
float InputManager::_yPosLast = 0;

void key_callback(GLFWwindow*, int, int, int, int);
void cursor_position_callback(GLFWwindow*, double, double);

void InputManager::pollEvents() {
    glfwPollEvents();
}

void InputManager::init(Config::Profile profile) {
    Logger::infoln("Initializing InputManager");

    _xPos = 0;
    _yPos = 0;
    _xPosLast = 0;
    _yPosLast = 0;

    glfwSetInputMode(Display::getWindow(), GLFW_STICKY_KEYS, 1);
    glfwSetKeyCallback(Display::getWindow(), key_callback);
    glfwSetCursorPosCallback(Display::getWindow(), cursor_position_callback);
}

bool InputManager::keyPressed(int key) {
    for (int _keyPres: _keyPress) {
        if (_keyPres == key) return true;
    }

    return false;
}

bool InputManager::keyDown(int key) {
    for (int i : _keyDown) {
        if (i == key) return true;
    }

    return false;
}

bool InputManager::keyReleased(int key) {
    for (int i : _keyRelease) {
        if (i == key) return true;
    }

    return false;
}

Vector2f InputManager::getMouse() {
    float x = (_xPos - Display::getWidth() / 2.0f) / Display::getWidth() * 2.0f;
    float y = (_yPos - Display::getHeight() / 2.0f) / Display::getHeight() * -2.0f;
    return Vector2f(x, y);
}

Vector2f InputManager::getMouseDelta() {
    float xl = (_xPosLast - Display::getWidth() / 2.0f) / Display::getWidth() * 2.0f;
    float yl = (_yPosLast - Display::getHeight() / 2.0f) / Display::getHeight() * -2.0f;
    float x = (_xPos - Display::getWidth() / 2.0f) / Display::getWidth() * 2.0f;
    float y = (_yPos - Display::getHeight() / 2.0f) / Display::getHeight() * -2.0f;
    float xres = (x - xl) / (Time::deltaTimef == 0 ? 0.001f : Time::deltaTimef);
    float yres = (y - yl) / (Time::deltaTimef == 0 ? 0.001f : Time::deltaTimef);
    return Vector2f(xres, yres);
}

void InputManager::setCursorMode(CursorMode mode) {
    glfwSetInputMode(Display::getWindow(), GLFW_CURSOR, (int) mode);
}

InputManager::CursorMode InputManager::getCursorMode() {
    return (CursorMode) glfwGetInputMode(Display::getWindow(), GLFW_CURSOR);
}

void InputManager::handleKey(int key, int action) {
    if (action == GLFW_PRESS) {
        _keyPress.push_back(key);
        _keyDown.push_back(key);
    } else if (action == GLFW_RELEASE) {
        _keyDown.erase(std::remove(_keyDown.begin(), _keyDown.end(), key), _keyDown.end());
        _keyRelease.push_back(key);
    }
}

void InputManager::handleMouse(float x, float y) {
    _xPos = x;
    _yPos = y;
}

void InputManager::update() {
    _xPosLast = _xPos;
    _yPosLast = _yPos;
    _keyPress.clear();
    _keyRelease.clear();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    InputManager::handleKey(key, action);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    InputManager::handleMouse((float) xpos, (float) ypos);
}