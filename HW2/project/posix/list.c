#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void insert(struct node **head, Task *task)
{
    struct node *node = malloc(sizeof(*node));
    if (node == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    node->task = task;
    node->next = *head;
    *head = node;
}

void delete(struct node **head, Task *task)
{
    struct node **cursor = head;

    while (*cursor != NULL)
    {
        if ((*cursor)->task == task ||
            strcmp((*cursor)->task->name, task->name) == 0)
        {
            struct node *removed = *cursor;
            *cursor = removed->next;
            free(removed);
            return;
        }
        cursor = &(*cursor)->next;
    }
}

void traverse(struct node *head)
{
    for (const struct node *node = head; node != NULL; node = node->next)
    {
        printf("[%s] [%d] [%d]\n", node->task->name, node->task->priority,
               node->task->burst);
    }
}
