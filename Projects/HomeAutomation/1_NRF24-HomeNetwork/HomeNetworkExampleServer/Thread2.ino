static msg_t Thread2(void *arg) {

  while (1) {
    // Do nothing.
    chThdSleepMilliseconds(10);
  }

  return 0;
}

