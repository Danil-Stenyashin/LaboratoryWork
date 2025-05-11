#include "include/Choice.h"
#include "include/utils.h"

Choice::Choice(std::string t, int c) : text(t), consequence(c) {}

int Choice::makeChoice() {
    print("Выбор: " + text);
    return consequence;
}
