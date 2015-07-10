static msg_t Thread2(void *arg) {
  chThdSleepMilliseconds(4000);

  while (1) {
    msgNode = homeNetworkExampleServer;
    msgContent = 1;
    //toggleMainLights();

    chThdSleepMilliseconds(2000);
  }

  return 0;
}

