#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct ListItem ListItem;

typedef struct {
	ListItem *head;
	ListItem *tail;
	size_t item_size;
	unsigned long size;
} LinkedList;

void linked_list_init(LinkedList *list, size_t item_size);
void linked_list_add(LinkedList *list, void *data);
void linked_list_add_at(LinkedList *list, void *data, int index);
bool linked_list_remove(LinkedList *list, void *data, int (*compare_func)(const void *, const void *));
bool linked_list_contains(LinkedList *list, void *data, int (*compare_func)(const void *, const void *));
bool linked_list_remove_at(LinkedList *list, int index);
unsigned long linked_list_size(LinkedList *list);
void linked_list_print(LinkedList *list, void (*print_item)(const void *));
void linked_list_destroy(LinkedList *list);

#endif
