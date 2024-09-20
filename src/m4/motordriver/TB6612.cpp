#include <m4\motordriver\TB6612.hpp>

m4::motordriver::TB6612::TB6612(int pin1, int pin2, int ch1, int ch2) {
    this->pin1  = pin1;
    this->pin2  = pin2;
    pwm_ch1     = ch1;
    pwm_ch1_max = pwm_ch1 == 1 ? 4 : 1;
    pwm_ch2     = ch2;
    pwm_ch2_max = pwm_ch2 == 1 ? 4 : 1;
}

void m4::motordriver::TB6612::setup() {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);

    ledcSetup(pwm_ch1, 12800, 8);
    ledcAttachPin(pin1, pwm_ch1);
    ledcWrite(pwm_ch1, 0);

    ledcSetup(pwm_ch2, 12800, 8);
    ledcAttachPin(pin2, pwm_ch2);
    ledcWrite(pwm_ch2, 0);

    ledcWrite(pwm_ch1, 255 * pwm_ch1_max);
    ledcWrite(pwm_ch2, 255 * pwm_ch2_max);
}

void m4::motordriver::TB6612::stop() {
    ledcWrite(pwm_ch1, LOW);
}

void m4::motordriver::TB6612::changeSpeed(int value) {
    speed = value;
    if (value > 0) {
        ledcWrite(pwm_ch1, value * pwm_ch1_max);
        ledcWrite(pwm_ch2, 0);
    } else if (value < 0) {
        ledcWrite(pwm_ch1, 0);
        ledcWrite(pwm_ch2, -value * pwm_ch2_max);
    } else {
        ledcWrite(pwm_ch1, 255 * pwm_ch1_max);
        ledcWrite(pwm_ch2, 255 * pwm_ch2_max);
    }
}

auto m4::motordriver::TB6612::serialize() const -> std::array<char, 16> {
    auto result = std::array<char, 16>();
    sprintf(result.data(), "speed: %d", speed);
    return result;
}
