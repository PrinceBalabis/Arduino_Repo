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
  // CTRL-SHIFT-ALT-K
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('g');
  delay(100);
  Keyboard.releaseAll();
}
