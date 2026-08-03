#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

void add(char *name, int priority, int burst);
void schedule(void);

#endif
