#ifndef INTERPRETCLOCK_H
#define INTERPRETCLOCK_H

#include <chrono>
#include <iostream>
#include <iomanip>

void positionClkOutput(const int, const char fillingCharacter = '0');

void interpretClk(const std::chrono::milliseconds&);

void interpretClk(const std::chrono::steady_clock::duration);

#endif //INTERPRETCLOCK_H
