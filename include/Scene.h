#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

class Scene {
private:
    std::vector<std::string> description;
public:
    Scene(const std::vector<std::string>& desc);
    void showScene();
};

#endif
