#include <m4/MusicPlayer.hpp>

m4::MusicPlayer::MusicPlayer() {
    serial_for_player.begin(9600);
    player.begin(serial_for_player);
    player.volume(1);
    track_id = 0;
}

void m4::MusicPlayer::playMusic(int musicNumber) {
    player.play(track_id);
}

void m4::MusicPlayer::stopMusic() {
    player.stop();
}
