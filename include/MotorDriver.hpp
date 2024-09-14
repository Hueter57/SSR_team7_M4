#pragma once

#include <Arduino.h>
// TB6612使用 Dual DCモータードライブキット用
// MotorDriver{エンコーダー入力1, エンコーダー入力2, モーター出力指定正, モーター出力指定負}

class MotorDriver {
public:
    int in1Pin;
    int in2Pin;

    int speed;  // 0 ~ -1024

    int pwmch1;
    int pwmch2;

    MotorDriver(int pin1, int pin2, int ch1, int ch2);

    void setup();

    void stop();

    void changeSpeed(int value);

    auto serialize() const -> std::array<char, 16>;
};