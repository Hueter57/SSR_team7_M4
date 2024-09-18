#include <Arduino.h>

#include <ESP32Servo.h>
#include <Ps3Controller.h>

#include <m4/Debug.hpp>
#include <m4/MusicPlayer.hpp>
#include <m4/State.hpp>
#include <m4/motordriver/SteppingMotor.hpp>
#include <m4/motordriver/TB6612.hpp>

#define NO_GLOBAL_SERIAL
#define DEBUG

auto serial = HardwareSerial(0);
auto state  = m4::State();

Servo steeringServo;           // サーボオブジェクトの定義
int   steeringServoPin = 16;   // サーボの制御ピンの制御用のピン(明るいほうのオレンジ(黄色?))
int   minUs            = 500;  // 最小のパルス幅
int   maxUs            = 2400;  // 最大のパルス幅

m4::motordriver::TB6612        mainMotor{27, 26, 1, 2};
m4::motordriver::TB6612        mastMotor{33, 32, 3, 4};
m4::motordriver::SteppingMotor handMotor{2, 4};

m4::MusicPlayer player{};

void ps3Setup();

void setup() {
    serial.begin(9600);

    ps3Setup();

    mainMotor.setup();
    mastMotor.setup();

    steeringServo.setPeriodHertz(50);                      // 50HzのPWMを出すという設定
    steeringServo.attach(steeringServoPin, minUs, maxUs);  // servoオブジェクトに定数を設定していく
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
    Ps3.begin("C4:DE:E2:C0:79:CE");
}
