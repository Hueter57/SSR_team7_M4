#include <m4\SteppingMotor.hpp>

m4::SteppingMotor::SteppingMotor(int p1, int p2) {
    pin1    = p1;
    pin2    = p2;
    nowStep = 0;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
}

auto m4::SteppingMotor::moveSteppingMotor(int value) -> void {
    if (value == 1) {
        stepUp();
    } else if (value == -1) {
        stepDown();
    }
}

auto m4::SteppingMotor::stepUp() -> void {
    digitalWrite(pin1, HIGH);
    if (nowStep) {
        nowStep = 0;
        digitalWrite(pin2, LOW);
    } else {
        nowStep = 1;
        digitalWrite(pin2, HIGH);
    }
}

auto m4::SteppingMotor::stepDown() -> void {
    digitalWrite(pin1, LOW);
    if (nowStep) {
        nowStep = 0;
        digitalWrite(pin2, LOW);
    } else {
        nowStep = 1;
        digitalWrite(pin2, HIGH);
    }
}