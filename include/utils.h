#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

void clearScreen();
void print(const std::string& text, int delay = 30);
int handleInput(int min, int max);

#endif
