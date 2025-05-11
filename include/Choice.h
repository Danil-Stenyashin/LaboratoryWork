#ifndef CHOICE_H
#define CHOICE_H

#include <string>

class Choice {
private:
    std::string text;
    int consequence;
public:
    Choice(std::string t, int c);
    int makeChoice();
};

#endif
