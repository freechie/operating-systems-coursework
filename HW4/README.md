# Virtual memory manager

Build the program with a C11 compiler:

```sh
cc -std=c11 -Wall -Wextra -pedantic virtual_memory_manager.c -o virtual_memory_manager
```

The program accepts a text file containing one logical address per line and
expects `BACKING_STORE.bin` in its working directory:

```sh
./virtual_memory_manager addresses.txt
```

The original course fixture is not included. Run the self-contained regression
test instead; it creates an original deterministic backing store and address
list in a temporary directory:

```sh
python3 test_virtual_memory_manager.py
```
