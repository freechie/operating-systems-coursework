CC ?= cc
CFLAGS ?= -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -pedantic

PROGRAMS = fcfs sjf rr priority priority_rr
COMMON_OBJECTS = driver.o list.o CPU.o

.PHONY: all clean

all: $(PROGRAMS)

fcfs: $(COMMON_OBJECTS) schedule_fcfs.o
	$(CC) $(CFLAGS) -o $@ $^

sjf: $(COMMON_OBJECTS) schedule_sjf.o
	$(CC) $(CFLAGS) -o $@ $^

rr: $(COMMON_OBJECTS) schedule_rr.o
	$(CC) $(CFLAGS) -o $@ $^

priority: $(COMMON_OBJECTS) schedule_priority.o
	$(CC) $(CFLAGS) -o $@ $^

priority_rr: $(COMMON_OBJECTS) schedule_priority_rr.o
	$(CC) $(CFLAGS) -o $@ $^

driver.o: driver.c schedulers.h
list.o: list.c list.h task.h
CPU.o: CPU.c cpu.h task.h
schedule_fcfs.o schedule_sjf.o schedule_rr.o schedule_priority.o schedule_priority_rr.o: task.h list.h schedulers.h cpu.h

clean:
	$(RM) $(PROGRAMS) *.o
