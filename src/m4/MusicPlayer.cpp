#include <m4/MusicPlayer.hpp>

m4::MusicPlayer::MusicPlayer() {
    serial_for_player.begin(9600);
    player.begin(serial_for_player);
    player.volume(20);
    track_id = 0;
}

auto m4::MusicPlayer::play_music_event(ps3_event_t event) -> void {
    if (player.isPlaying()) {
        return;
    }

    const ps3_button_t button_down = event.button_down;
    if (event.button_down.circle) {
        player.play(1);
    } else if (button_down.cross) {
        player.play(2);
    } else if (button_down.square) {
        player.play(3);
    } else if (button_down.triangle) {
        player.play(4);
    } else if (button_down.up) {
        player.play(5);
    } else if (button_down.down) {
        player.play(6);
    } else if (button_down.left) {
        player.play(7);
    } else if (button_down.right) {
        player.play(8);
    } else if (button_down.select) {
        stop_music();
    }
}

void m4::MusicPlayer::play_music_number(int music_number) {
    if (player.isPlaying()) {
        player.stop();
    }
    track_id = music_number;
    player.play(music_number);
}

void m4::MusicPlayer::stop_music() {
    player.stop();
}
