# pts - primitive task sheduler
  It is cooperative sheduler. It has priority, every task should finished every call, can activate other task (but not itself). Sheduler ends chain when all tasks finished and can be run again or hibernate MCU. Only 5 functions. Every task used RAM for 2 pointers and argument/status.
  Limitation: argument can not be zero ('0');
