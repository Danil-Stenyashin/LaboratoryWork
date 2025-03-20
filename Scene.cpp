#include "Scene.h"
#include <iostream>

Scene::Scene(const std::string& desc) : description(desc) {}

void Scene::display() {
    std::cout << description << std::endl;
}

