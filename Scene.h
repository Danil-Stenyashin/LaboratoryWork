#ifndef SCENE_H
#define SCENE_H

#include <string>

class Scene {
public:
    std::string description;

    Scene(const std::string& desc);
    void display();
};

#endif // SCENE_H

