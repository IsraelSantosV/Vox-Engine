//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_CONTROLLERS_CPP
#define FP_OPENGL_CONTROLLERS_CPP

#define TO_RADIANS 3.14/180.0
#define GROUND_SCALE 50
#define GROUND_HEIGHT 5
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include "Tools.cpp"
#include "InputManager.cpp"
#include "Models.cpp"

class Camera {
private:
    int m_ScreenWidth;
    int m_ScreenHeight;
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_VerticalLimit;
    float m_Speed;
    float m_Sensibility;
    bool m_CursorLocked;
    static Camera* m_Instance;
    Camera() = default;
public:
    static Camera* getInstance(){
        if(m_Instance == nullptr){
            m_Instance = new Camera();
        }

        return m_Instance;
    }

    void setScreenSize(int width, int height){
        m_ScreenWidth = width;
        m_ScreenHeight = height;
    }

    void initialize(float speed, float smoothCamera){
        m_Speed = speed;
        m_Sensibility = smoothCamera;
    }

    void receiveMousePosition(int x, int y){
        float sensibility = getSensibility();
        Vector3 currentRot = getRotation();
        float currentYaw = currentRot.x;
        float currentPitch = currentRot.y;

        float targetYaw = isFreeze() ? currentYaw : currentYaw + (float)x/sensibility;
        float targetPitch = isFreeze() ? currentPitch : currentPitch + (float)y/sensibility;
        setRotation(Vector3(targetYaw, targetPitch));
    }

    void updateMovement(){
        InputKey* forward = InputManager::getInstance()->getKey("Vertical", true);
        InputKey* backward = InputManager::getInstance()->getKey("Vertical", false);
        InputKey* right = InputManager::getInstance()->getKey("Horizontal", true);
        InputKey* left = InputManager::getInstance()->getKey("Horizontal", false);

        float yaw = getRotation().x;
        float pitch = getRotation().y;

        if(forward != nullptr && forward->isPressed()){
            setMovement(Vector3(
                    getPosition().x + cos((yaw+90)*TO_RADIANS)/getSpeed(), 0,
                    getPosition().z - sin((yaw+90)*TO_RADIANS)/getSpeed()
            ));
        }
        if(backward != nullptr && backward->isPressed()){
            setMovement(Vector3(
                    getPosition().x + cos((yaw+90+180)*TO_RADIANS)/getSpeed(), 0,
                    getPosition().z - sin((yaw+90+180)*TO_RADIANS)/getSpeed()
            ));
        }
        if(right != nullptr && right->isPressed()){
            setMovement(Vector3(
                    getPosition().x + cos((yaw+90-90)*TO_RADIANS)/getSpeed(), 0,
                    getPosition().z - sin((yaw+90-90)*TO_RADIANS)/getSpeed()
            ));
        }
        if(left != nullptr && left->isPressed()){
            setMovement(Vector3(
                    getPosition().x + cos((yaw+90+90)*TO_RADIANS)/getSpeed(), 0,
                    getPosition().z - sin((yaw+90+90)*TO_RADIANS)/getSpeed()
            ));
        }

        glRotatef(-pitch,1.0,0.0,0.0); // Along X axis
        glRotatef(-yaw,0.0,1.0,0.0);    //Along Y axis
        glTranslatef(-getPosition().x,0.0,-getPosition().z);
    }

    void setVerticalLimit(Vector3 limit){
        m_VerticalLimit.set(limit.x, limit.y, limit.z);
    }

    void setMovement(Vector3 position){
        m_Position.set(position.x, position.y, position.z);
    }

    void setRotation(Vector3 rotation){
        float clampedPitch = rotation.y;
        if(clampedPitch >= m_VerticalLimit.x){
            clampedPitch = m_VerticalLimit.x;
        }
        if(clampedPitch <= -m_VerticalLimit.y){
            clampedPitch = -m_VerticalLimit.y;
        }

        m_Rotation.set(rotation.x, clampedPitch, rotation.z);
    }
    Vector3 getPosition() { return m_Position; }
    Vector3 getRotation() { return m_Rotation; }
    float getSpeed(){ return m_Speed; }
    float getSensibility() { return m_Sensibility; }
    bool cursorIsLocked() { return m_CursorLocked; }
    bool isFreeze() { return !cursorIsLocked(); }

    void setCursorLockState(bool locked){
        m_CursorLocked = locked;
        if(m_CursorLocked){
            glutWarpPointer(m_ScreenWidth/2,m_ScreenHeight/2);
            glutSetCursor(GLUT_CURSOR_NONE);
        }
        else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    void registerActionTriggers(){
        InputKey *escapeKey = InputManager::getInstance()->getKey(ESCAPE);
        if (escapeKey != nullptr) {
            escapeKey->registerAction([](){
                Camera* currentCamera = Camera::getInstance();
                currentCamera->setCursorLockState(!currentCamera->cursorIsLocked());
            }, ONE_TIME);
        }
    }
};

class Grid {
private:
    int m_GridSize;
    int m_LateralSize;
    int m_YLevel;
    int m_SectionSize;
    int m_SectionAmount;
    Section** m_Sections;
public:
    Grid(int gridSize, int yLevel, int sectionSize){
        m_GridSize = gridSize;
        m_YLevel = yLevel;
        m_SectionSize = sectionSize;

        m_SectionAmount = (m_GridSize * m_GridSize) / sectionSize;
        m_LateralSize = sqrt(m_SectionAmount);
        m_Sections = new Section*[m_LateralSize];

        int currentPos = 0;
        int currentID = 0;

        for(int x = 0; x < m_LateralSize; x++){
            for(int z = 0; z < m_LateralSize; z++){
                cout << currentPos << " ";
                m_Sections[x,z] = new Section(currentID, Vector3(currentPos, yLevel, currentPos));
                currentPos += sectionSize;
                currentID++;
            }
        }

        cout << endl;
    }

    ~Grid(){
        for(int i = 0; i < m_LateralSize; i++){
            delete m_Sections[i];
        }

        delete[] m_Sections;
    }

    void debugGrid(){
        for(int x = 0; x < m_LateralSize; x++){
            for(int z = 0; z < m_LateralSize; z++){
                Vector3 position = m_Sections[x,z]->getPosition();
                cout << '[' << x << ',' << z << "]: (" << position.x << ',' << position.z << ")   ";
            }

            cout << endl;
        }
    }

    Section* getSection(int x, int z){
        Section* selectedSection = nullptr;
        for(int x = 0; x < m_LateralSize; x++){
            for(int z = 0; z < m_LateralSize; z++){
                Section* currentSection = m_Sections[x,z];
                Vector3 currentPos = currentSection->getPosition();
                if(x >= currentPos.x && z >= currentPos.z){
                    selectedSection = currentSection;
                }
            }
        }

        return selectedSection;
    }

};

class Scenario {
private:
    vector<WorldObject*> m_RuntimeObjects;
    static Scenario* m_Instance;
    Grid* m_Grid;

    Scenario(){
        m_Grid = new Grid(GROUND_SCALE, 0, 100);
        m_Grid->debugGrid();

        WorldObject* cube = instantiate("Cube");
        cube->setMesh(new CubeMesh(cube, false));
        cube->getTransform()->setScale(Vector3(2,3,5));
        cube->getTransform()->setPosition(Vector3(-5,0,0));
        cube->getMesh()->setColor(Vector3(0,0,1));
    }

    void registerObject(WorldObject* obj){
        if(obj == nullptr) return;
        m_RuntimeObjects.push_back(obj);
    }
public:
    static Scenario* getInstance(){
        if(m_Instance == nullptr){
            m_Instance = new Scenario();
        }

        return m_Instance;
    }

    void drawScenario(){
        for(auto obj : m_RuntimeObjects){
            if(obj == nullptr || !obj->isActive()) continue;
            if(obj->getMesh() == nullptr) continue;
            obj->getMesh()->draw();
        }
    }

    WorldObject* instantiate(string name, WorldObject* parent = nullptr){
        WorldObject* newObject = new WorldObject(name, parent);
        registerObject(newObject);
        return newObject;
    }
};

#endif //FP_OPENGL_CONTROLLERS_CPP