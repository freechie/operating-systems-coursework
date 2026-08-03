#ifndef LIST_H
#define LIST_H

#include "task.h"

struct node
{
    Task *task;
    struct node *next;
};

void insert(struct node **head, Task *task);
void delete(struct node **head, Task *task);
void traverse(struct node *head);

#endif
