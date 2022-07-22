#include <stdio.h>
#include <stdlib.h>

struct list_node {
    struct list_node *prev;
    struct list_head *next;
};

typedef struct list_node list_head;

int list_init(struct list_node *node)
{
    node->prev = NULL;
    node->next = NULL;
    
    return 0;
}

int list_add(struct list_node *node, struct list_node *head)
{
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
    
    return 0;
}

int list_free(struct list_node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = node;
    node->next = node;
    
    return 0;
}
