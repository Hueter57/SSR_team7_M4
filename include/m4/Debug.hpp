#pragma once

#include <Arduino.h>
#include <Ps3Controller.h>
#include <m4/State.hpp>
#include <m4/motordriver/TB6612.hpp>

namespace m4::debug {

auto state_print(HardwareSerial &serial, const State &state) -> void {
    serial.printf("state: { %s }\n", state.serialize().data());
}

auto motor_driver_state_print(HardwareSerial &serial, const m4::motordriver::TB6612 &motorDriver) -> void {
    serial.printf("motor: { %s }\n", motorDriver.serialize().data());
}

auto ps3_data_print(HardwareSerial &serial, const ps3_t &ps3Data) -> void {
    const auto stick = ps3Data.analog.stick;

    char batteryMode[16] = "";
    switch (ps3Data.status.battery) {
    case 238:
        strcpy(batteryMode, "CHARGING");
        break;
    case 5:
        strcpy(batteryMode, "FULL");
        break;
    case 4:
        strcpy(batteryMode, "HIGH");
        break;
    case 3:
        strcpy(batteryMode, "LOW");
        break;
    case 2:
        strcpy(batteryMode, "DYING");
        break;
    case 1:
        strcpy(batteryMode, "SHUTDOWN");
        break;
    default:
        strcpy(batteryMode, "UNDEFINED");
        break;
    }

    serial.printf("ps3-data: { stick: { left: { x: %d, y: %d }, right: { x: %d, y: %d } }, battery: %s }\n", stick.lx,
                  stick.ly, stick.rx, stick.ry, batteryMode);
}

auto ps3_event_print(HardwareSerial &serial, const ps3_event_t &ps3Event) -> void {
    const auto buttonUp   = ps3Event.button_up;
    const auto buttonDown = ps3Event.button_down;

    if (buttonUp.l1) {
        serial.println("ps3-event-info: Start pressing the l1 button");
    }
    if (buttonUp.l2) {
        serial.println("ps3-event-info: Start pressing the l2 button");
    }
    // ...
    if (buttonDown.l1) {
        serial.println("ps3-event-info: Released the l1 button");
    }
    if (buttonDown.l2) {
        serial.println("ps3-event-info: Released the l2 button");
    }
}
}  // namespace m4::debug
