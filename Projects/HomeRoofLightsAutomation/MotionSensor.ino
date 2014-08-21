static void vMotionSensorTask(void *pvParameters) {
  while (1) {
    // Sleep for 50 milliseconds.
    vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
  }
}

