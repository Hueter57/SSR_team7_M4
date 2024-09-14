#include <m4/State.hpp>

auto m4::State::getServoOutput() -> int {
    return (int)(direction * 0.75) + 90;
}
auto m4::State::getMotorOutput() -> int {
    return (int)(forward * 10.23);
}
auto m4::State::getMastMove() -> int {
    return mastMove;
}
auto m4::State::getHand() -> int {
    return hand;
}
auto m4::State::update(ps3_t data) -> void {
    const auto leftX  = data.analog.stick.lx;
    const auto leftY  = data.analog.stick.ly;
    const auto rightX = data.analog.stick.rx;
    const auto rightY = data.analog.stick.ry;

    auto signX = leftX > 0 ? 1 : -1;
    direction  = signX * constrain(abs(leftX) - 15, 0, 100);
    auto signY = rightY > 0 ? -1 : 1;
    forward    = signY * constrain(abs(rightY) - 15, 0, 100);

    if (data.button.l1) {
        mastMove = 1;
    } else if (data.button.l2) {
        mastMove = -1;
    } else {
        mastMove = 0;
    }

    if (data.button.r1) {
        hand = 1;
    } else if (data.button.r2) {
        hand = -1;
    } else {
        hand = 0;
    }
}
auto m4::State::serialize() const -> std::array<char, 64> {
    auto result = std::array<char, 64>();
    sprintf(result.data(), "direction: %d, forward: %d, mastMove: %d, hand: %d\n", direction, forward, mastMove, hand);
    return result;
}
