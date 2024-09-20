#pragma once

#include <Arduino.h>
#include <DFPlayerMini_Fast.h>
#include <Ps3Controller.h>

namespace m4 {
class MusicPlayer {
private:
    HardwareSerial    serial_for_player{2};
    DFPlayerMini_Fast player;
    int               track_id;

public:
    MusicPlayer();
    auto play_music_event(ps3_event_t event) -> void;
    auto play_music_number(int music_number) -> void;
    auto stop_music() -> void;
};

}  // namespace m4