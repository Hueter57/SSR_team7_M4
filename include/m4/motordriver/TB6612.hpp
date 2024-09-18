#pragma once

#include <Arduino.h>
// TB6612使用 Dual DCモータードライブキット用
// TB6612{エンコーダー入力1, エンコーダー入力2, モーター出力指定正, モーター出力指定負}
namespace m4::motordriver {
class TB6612 {
public:
    int in1Pin;
    int in2Pin;

    int speed;  // 0 ~ -1024

    int pwmch1;
    int pwmch2;

    TB6612(int pin1, int pin2, int ch1, int ch2);

    void setup();

    void stop();

    void changeSpeed(int value);

    auto serialize() const -> std::array<char, 16>;
};
}  // namespace m4::motordriver