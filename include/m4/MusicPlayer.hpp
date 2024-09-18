#pragma once

#include <Arduino.h>
#include <DFPlayerMini_Fast.h>

namespace m4 {
class MusicPlayer {
private:
    HardwareSerial    serial_for_player{2};
    DFPlayerMini_Fast player;
    int               track_id;

public:
    MusicPlayer();
    auto playMusic(int music_number) -> void;
    auto stopMusic() -> void;
};

}  // namespace m4