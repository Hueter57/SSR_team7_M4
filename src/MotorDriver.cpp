#include <MotorDriver.hpp>

MotorDriver::MotorDriver(int pin1, int pin2, int ch1, int ch2) {
    in1Pin  = pin1;
    in2Pin  = pin2;
    pwmch1   = ch1;
    pwmch2   = ch2;
}

void MotorDriver::setup() {
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);

    ledcSetup(pwmch1, 100000, 8);
    ledcAttachPin(in1Pin, pwmch1);
    ledcWrite(pwmch1, 0);

    ledcSetup(pwmch2, 100000, 8);
    ledcAttachPin(in2Pin, pwmch2);
    ledcWrite(pwmch2, 0);

    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, HIGH);
}

void MotorDriver::stop() {
    ledcWrite(pwmch1, LOW);
}

void MotorDriver::changeSpeed(int value) {
    speed = value;
    // Serial.print(value);
    if (value > 0) {
        digitalWrite(in2Pin, LOW);
        ledcWrite(pwmch1, value);
    } else if (value < 0) {
        digitalWrite(in1Pin, LOW);
        ledcWrite(pwmch2, -value);
    } else {
        ledcWrite(pwmch1, 0);
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, HIGH);
    }
}

auto MotorDriver::serialize() const -> std::array<char, 16> {
    auto result = std::array<char, 16>();
    sprintf(result.data(), "speed: %d", speed);
    return result;
}
