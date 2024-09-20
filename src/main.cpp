#include <Arduino.h>

#include <ESP32Servo.h>
#include <Ps3Controller.h>

#include <m4/Assign.hpp>
#include <m4/Debug.hpp>
#include <m4/MusicPlayer.hpp>
#include <m4/State.hpp>
#include <m4/motordriver/SteppingMotor.hpp>
#include <m4/motordriver/TB6612.hpp>

#define NO_GLOBAL_SERIAL
#define DEBUG

auto serial = HardwareSerial(0);
auto state  = m4::State();

Servo steeringServo;
int   minUs = 500;
int   maxUs = 2400;

m4::motordriver::TB6612 mainMotor{m4::assign::MAIN_MOTOR_PIN1, m4::assign::MAIN_MOTOR_PIN2, m4::assign::MAIN_MOTOR_CH1,
                                  m4::assign::MAIN_MOTOR_CH2};
m4::motordriver::TB6612 mastMotor{m4::assign::MAST_MOTOR_PIN1, m4::assign::MAST_MOTOR_PIN2, m4::assign::MAST_MOTOR_CH1,
                                  m4::assign::MAST_MOTOR_CH2};

m4::motordriver::SteppingMotor handMotor{m4::assign::HAND_MOTOR_DIR, m4::assign::HAND_MOTOR_STEP};

m4::MusicPlayer player{};

void ps3Setup();

void setup() {
    serial.begin(9600);

    ps3Setup();

    mainMotor.setup();
    mastMotor.setup();

    steeringServo.setPeriodHertz(50);                           // 50HzのPWMを出すという設定
    steeringServo.attach(m4::assign::SERVO_PIN, minUs, maxUs);  // servoオブジェクトに定数を設定していく
    steeringServo.write(90);
}

void loop() {
    if (!Ps3.isConnected()) {
        return;
    }
    state.update(Ps3.data);
    mainMotor.changeSpeed(state.getMotorOutput());
    steeringServo.write(state.getServoOutput());
    mastMotor.changeSpeed(state.getMastMove());
    handMotor.moveSteppingMotor(state.getHand());
    player.play_music_event(Ps3.event);
#ifdef DEBUG
    m4::debug::state_print(serial, state);
    // m4::debug::motor_driver_state_print(serial, mainMotor);
    // m4::debug::ps3_data_print(serial, Ps3.data);
    // m4::debug::ps3_event_print(serial, Ps3.event);
#endif
}

// --- define functions ---

// --- ps3Control ---
void notify() {
}

void onConnect() {
    // これがないと動かない
#ifdef DEBUG
    serial.println("Connected.");
#endif
    delay(500);
    Ps3.setPlayer(2);
}

void onDisconnect() {
#ifdef DEBUG
    serial.println("DisConnected!.");
#endif
}

void ps3Setup() {
    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.attachOnDisconnect(onDisconnect);
    Ps3.begin(m4::assign::MAC_ADRESS);
}
