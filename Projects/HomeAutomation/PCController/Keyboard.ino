/*
 * OBS! Don't forget these are just keyboard shortcuts!
 * You must have setup NirCmd on the computer together with NirCmd keyboard shortcuts!
 *
 */

void pcDisableMonitors() {
  // CTRL-SHIFT-ALT-L
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('h');
  delay(100);
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
