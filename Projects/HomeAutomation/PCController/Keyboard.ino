void DisableMonitors() {
  // CTRL-SHIFT-ALT-L
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('l');
  delay(100);
  Keyboard.releaseAll();
}

