/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

int32_t executeCommand = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{

  while (1)
  {
    // Wait for signal to run
    chSemWait(&cmdExSem);

    switch (executeCommand) {
      case cmdSetPCDisableMonitors:
        pcDisableMonitors();
        break;
      case cmdSetPCDisableMonitors:
        pcEnableMonitors();
        break;
    }
  }
  return 0;
}
