#pragma once

#include <Ps3Controller.h>

namespace m4 {
class State {
private:
    int direction;
    int forward;
    int mastMove;
    int hand;

public:
    auto getServoOutput() -> int ;
    auto getMotorOutput() -> int;
    auto getMastMove() -> int;
    auto getHand() -> int;
    
    auto update(ps3_t data) -> void;
    auto serialize() const -> std::array<char, 64>;
};
}  // namespace m4