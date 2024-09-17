#pragma once

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

namespace m4 {
class MusicPlayer {
private:
    int                 musicNumber = 1;
    DFRobotDFPlayerMini myDFPlayer;
    HardwareSerial      myHardwareSerial{2};

public:
    MusicPlayer();
    void playMusic();
    void changeMusic();
    void stopMusic();

};

}  // namespace m4