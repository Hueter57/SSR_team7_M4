#pragma once

#include <Arduino.h>

namespace m4 {
class SteppingMotor {
private:
    int nowStep;
    int pin1;
    int pin2;

public:
    SteppingMotor(int p1, int p2);
    auto moveSteppingMotor(int value) -> void;
    auto stepUp() -> void;
    auto stepDown() -> void;
};
}  // namespace m4