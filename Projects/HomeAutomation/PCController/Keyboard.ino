/*
 * OBS! Don't forget these are just keyboard shortcuts!
 * You must have setup NirCmd on the computer together with NirCmd keyboard shortcuts!
 *
 */

void pcDisableMonitors() {
  // CTRL-SHIFT-ALT-H
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('h');
  delay(50);
  Keyboard.releaseAll();
}

void pcEnableMonitors() {
  // Just toggle Caps lock on and off in order to wake monitors
  Keyboard.press(KEY_CAPS_LOCK);
  delay(50);
  Keyboard.release(KEY_CAPS_LOCK);
  Keyboard.press(KEY_CAPS_LOCK);
  delay(50);
  Keyboard.release(KEY_CAPS_LOCK);
}

void pcIncreaseVolume() {
  // CTRL-SHIFT-ALT-V
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('v');
  delay(50);
  Keyboard.releaseAll();
}

void pcDecreaseVolume() {
  // CTRL-SHIFT-ALT-G
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('g');
  delay(50);
  Keyboard.releaseAll();
}

void pcSetVolumePresetLow() {
  // CTRL-SHIFT-ALT-U
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('U');
  delay(50);
  Keyboard.releaseAll();
}

void pcSetVolumePresetMedium() {
  // CTRL-SHIFT-ALT-I
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('i');
  delay(50);
  Keyboard.releaseAll();
}

void pcSetVolumePresetMax() {
  // CTRL-SHIFT-ALT-O
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('o');
  delay(50);
  Keyboard.releaseAll();
}


void pcMuteOn() {
  // CTRL-SHIFT-ALT-X
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('x');
  delay(50);
  Keyboard.releaseAll();
}

void pcMuteOff() {
  // CTRL-SHIFT-ALT-Z
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('z');
  delay(50);
  Keyboard.releaseAll();
}

void pcSpotifyStart() {
  // CTRL-SHIFT-ALT-S
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('s');
  delay(50);
  Keyboard.releaseAll();
}

/*
 * WOW! Väldig process för att starta Spotify playlist....
 *
 * Tidslinje:
 * Ctrl-L (Give focus to address/search field )
 * CTRL-A (Select text field)
 * Backspace (Clear text field)
 * Type "pulse cross" (to search for Pulse CROSSFIT playlist)
 * Arrow down (To focus on Pulse CROSSFIT playlist)
 * Enter (To choose playlist)
 * Tab (To shift focus to playlist)
 * Enter (To activate focus to playlist)
 * 7x tab (To shift focus to song lists)
 * Enter (To play the first song on the playlist)
 * Done!
 */
void pcSpotifyStartPlaylistWorkout() {
  initializeSpotifyStartPlaylist();

  //Type "pulse cross" (to search for Pulse CROSSFIT playlist)
  Keyboard.print("pulse cross");

  continueSpotifyStartPlaylist();
}

void pcSpotifyStartPlaylistDinner() {
  initializeSpotifyStartPlaylist();

  //Type "pulse cross" (to search for Pulse CROSSFIT playlist)
  Keyboard.print("dinner with friends");

  continueSpotifyStartPlaylist();
}

void initializeSpotifyStartPlaylist() {
  pcSpotifyStart(); // Start or focus on Spotify
  pcSetVolumePresetMedium(); //Set volume to Medium
  delay(7000); // Wait for Spotify to load/start

  //Ctrl-L (Give focus to address/search field )
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('l');
  delay(1);
  Keyboard.releaseAll();

  delay(100); // Wait for Spotify to load

  //CTRL - A (Select text field)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
  delay(1);
  Keyboard.releaseAll();

  delay(10); // Wait for Spotify to load

  //Backspace (Clear text field)
  Keyboard.press(KEY_BACKSPACE);
  delay(1);
  Keyboard.releaseAll();

  delay(500); // Wait for Spotify to load
}

void continueSpotifyStartPlaylist() {

  delay(3000); // Wait for Spotify to load search

  //Arrow down (To focus on Pulse CROSSFIT playlist)
  Keyboard.press(KEY_DOWN_ARROW);
  delay(1);
  Keyboard.releaseAll();

  delay(10); // Wait for Spotify to load

  //Enter (To choose playlist)
  Keyboard.press(KEY_RETURN);
  delay(1);
  Keyboard.releaseAll();

  delay(1000); // Wait for Spotify to load playlist page

  //Tab (To shift focus to playlist)
  Keyboard.press(KEY_TAB);
  delay(1);
  Keyboard.releaseAll();

  delay(10); // Wait for Spotify to load

  //Enter (To activate focus to playlist)
  Keyboard.press(KEY_RETURN);
  delay(1);
  Keyboard.releaseAll();

  delay(10); // Wait for Spotify to load

  //7x tab (To shift focus to song lists)
  Keyboard.press(KEY_TAB);
  delay(1);
  Keyboard.releaseAll();
  Keyboard.press(KEY_TAB);
  delay(1);
  Keyboard.releaseAll();
  Keyboard.press(KEY_TAB);
  delay(1);
  Keyboard.releaseAll();
  Keyboard.press(KEY_TAB);
  delay(1);
  Keyboard.releaseAll();
  Keyboard.press(KEY_TAB);
  delay(1);
  Keyboard.releaseAll();
  Keyboard.press(KEY_TAB);
  delay(1);
  Keyboard.releaseAll();
  Keyboard.press(KEY_TAB);
  delay(1);
  Keyboard.releaseAll();

  delay(50); // Wait for Spotify to catch up

  //Press down arrow random times to randomize first song!
  for (int i = 0; i < random(50); i++) {
    Keyboard.press(KEY_DOWN_ARROW);
    delay(10);
    Keyboard.releaseAll();
  }

  delay(10); // Wait for Spotify to load

  //Enter (To play the first song on the playlist)
  Keyboard.press(KEY_RETURN);
  delay(1);
  Keyboard.releaseAll();
}

