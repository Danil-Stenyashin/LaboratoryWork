#ifndef CHOICE_H
#define CHOICE_H

#include <string>

class Choice {
public:
    std::string text;
    int nextSceneID;

    Choice(const std::string& text, int nextSceneID);
};

#endif // CHOICE_H

