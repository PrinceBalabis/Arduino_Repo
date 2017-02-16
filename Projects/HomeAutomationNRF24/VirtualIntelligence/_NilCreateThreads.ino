/*
 * This code has to be AFTER the threads, meaning that is why this code is on its own tab,
 * with "_"(underscore) in its name, so its the last tab, because Arduino loads the code in order of tabs
 *
 * Threads static table, one entry per thread.  A thread's priority is
 * determined by its position in the table with highest priority first.
 *
 * These threads start with a null argument.  A thread's name may also
 * be null to save RAM since the name is currently not used.
 */
NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY(NULL, HomeNetworkThread, NULL, homeNetworkThread, sizeof(homeNetworkThread))
NIL_THREADS_TABLE_ENTRY(NULL, CommandExecutioner, NULL, commandExecutioner, sizeof(commandExecutioner))
NIL_THREADS_TABLE_ENTRY(NULL, VirtualIntelligence, NULL, virtualIntelligence, sizeof(virtualIntelligence))
NIL_THREADS_TABLE_END()

