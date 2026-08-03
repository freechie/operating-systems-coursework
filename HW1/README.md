# Processes and interprocess communication

`pipes.c` and `shared_memory.c` measure the elapsed time of a child command
while passing its start time to the parent through two different IPC
mechanisms.

```sh
cc -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -pedantic pipes.c -o pipes
cc -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -pedantic shared_memory.c -o shared_memory

./pipes /usr/bin/true
./shared_memory /usr/bin/true
```

`hundred.c` and `racer.c` are a separate process-and-pipe exercise. Build both
programs in this directory because `hundred` launches `./racer`.
