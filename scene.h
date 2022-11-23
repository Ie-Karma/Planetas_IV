#pragma once
#include "common.h"
#include "object.h"
#include "camera.h"
#include "spatialHashing.h"

class Scene {

public:
    Camera* cam = nullptr;
    std::map<int, Object*>* objList = nullptr;

    SpatialHashing* sceneGrid = nullptr;


public:

    std::map<int, Object*>* addedObjList = nullptr;
    std::map<float, Object*, std::greater<float>>* orderedObjList = nullptr;

    Scene();
    void setCamera(Camera* cam);
    Camera* getCamera();
    void addObject(Object* obj);
    void deleteObject(Object* obj);
    std::map<int, Object*>* getObjList();
    void step(double timeStep);

    std::vector<Object*>* getCollisions(int idType, Object* obj);
    ~Scene();

};
