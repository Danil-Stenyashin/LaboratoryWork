#include "include/Scene.h"
#include "include/utils.h"

Scene::Scene(const std::vector<std::string>& desc) : description(desc) {}

void Scene::showScene() {
    for (const std::string& line : description) {
        print(line);
    }
}
