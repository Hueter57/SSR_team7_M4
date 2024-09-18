#include <m4/MusicPlayer.hpp>

m4::MusicPlayer::MusicPlayer() {
    myHardwareSerial.begin(9600, SERIAL_8N1, 14, 12);
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    myDFPlayer.begin(myHardwareSerial);

    myDFPlayer.volume(10);  //Set volume value. From 0 to 30
}

void m4::MusicPlayer::playMusic() {
    if (myDFPlayer.available()) {
        myDFPlayer.play(musicNumber);
    }
}

void m4::MusicPlayer::stopMusic() {
    myDFPlayer.stop();
}
