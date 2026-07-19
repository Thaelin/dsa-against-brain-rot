#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListItem {
    void *data;
    struct ListItem *next;
    struct ListItem *prev;
};

/**
 * Initializes list's memory.
 */
void linked_list_init(LinkedList *list, size_t item_size) {
    list->head = NULL;
    list->tail = NULL;
    list->item_size = item_size;
    list->size = 0L;
}

/**
 * Adds an item to the end of the list. O(1).
 */
void linked_list_add(LinkedList *list, void *data) {
    ListItem * new_item = (ListItem *) malloc(sizeof(ListItem));
    new_item->data = malloc(list->item_size);
    memcpy(new_item->data, data, list->item_size);
    new_item->next = NULL;
    new_item->prev = list->tail;
    
    ListItem * current = list->head;

    if (current == NULL) {
        list->head = new_item;
        list->tail = new_item;
        list->size++;
        return;
    }

    list->tail->next = new_item;
    list->tail = new_item;
    list->size++;
}

/**
 * Insert an item to the specified position. Traversal is optimized to O(n/2). Insertions at head/tail are O(1).
 */
void linked_list_add_at(LinkedList *list, void *data, int index) {
    if (list == NULL || index < 0) {
        return;
    }

    size_t position = (size_t) index;

    if (position > list->size) {
        return;
    }

    ListItem * new_item = (ListItem *) malloc(sizeof(ListItem));
    if (new_item == NULL) {
        return;
    }
    new_item->data = malloc(list->item_size);
    if (new_item->data == NULL) {
        free(new_item);
        return;
    }
    memcpy(new_item->data, data, list->item_size);

    if (list->size == 0) {
        new_item->next = NULL;
        new_item->prev = NULL;
        list->head = new_item;
        list->tail = new_item;
    } else if (index == 0) {
        new_item->next = list->head;
        new_item->prev = NULL;
        list->head->prev = new_item;
        list->head = new_item;
    } else if (position == list->size) {
        new_item->next = NULL;
        new_item->prev = list->tail;
        list->tail->next = new_item;
        list->tail = new_item;
    } else {
        ListItem *item;

        if (position < list->size / 2) {
            item = list->head;
            for (size_t i = 0; i < position; i++) {
                item = item->next;
            }
        } else {
            item = list->tail;
            for (size_t i = list->size - 1; i > position; i--) {
                item = item->prev;
            }
        }

        new_item->prev = item->prev;
        new_item->next = item;
        item->prev->next = new_item;
        item->prev = new_item;
    }

    list->size++;
}

/**
 * Remove specific item from the list, comparator function is provided as an callback.
 * Returns true if item was deleted and false if not. 
 * Deletes only first matching occurence.
 * O(n).
 */
bool linked_list_remove(LinkedList *list, void *data, int (*compare_func)(const void *, const void *)) {
    if (list == NULL) {
        return false;
    }

    ListItem *item = list->head;

    while (item != NULL) {
        if (compare_func(item->data, data) == 0) {
            ListItem *next_item = item->next;
            ListItem *prev_item = item->prev;

            if (prev_item != NULL) {
                prev_item->next = next_item;
            } else {
                list->head = next_item;
            }

            if (item->next != NULL) {
                next_item->prev = prev_item;
            } else {
                list->tail = prev_item;
            }

            free(item->data);
            free(item);

            list->size--;
            return true;
        }
        item = item->next;
    }
    return false;
}

/**
 * Returns true if specific item is in the list, comparator function is provided as an callback. O(n).
 */
bool linked_list_contains(LinkedList *list, void *data, int (*compare_func)(const void *, const void *)) {
    if (list == NULL) {
        return false;
    }

    ListItem *item = list->head;

    while (item != NULL) {
        if (compare_func(item->data, data) == 0) {
            return true;
        }
        item = item->next;
    }
    return false;
}

/**
 * Remove item at specified index from the list.
 * Returns true if item was deleted and false if not. O(n/2).
 */
bool linked_list_remove_at(LinkedList *list, int index) {
    if (list == NULL || list->head == NULL || index < 0) {
        return false;
    }

    size_t position = (size_t) index;

    if (position >= list->size) {
        return false;
    }

    ListItem *item;

    if (position < list->size / 2) {
        item = list->head;
        for (size_t i = 0; i < position; i++) {
            item = item->next;
        }
    } else {
        item = list->tail;
        for (size_t i = list->size - 1; i > position; i--) {
            item = item->prev;
        }
    }

    ListItem *prev_item = item->prev;
    ListItem *next_item = item->next;

    if (prev_item == NULL) {
        list->head = next_item;
    } else {
        prev_item->next = next_item;
    }

    if (next_item == NULL) {
        list->tail = prev_item;
    } else {
        next_item->prev = prev_item;
    }

    free(item->data);
    free(item);

    list->size--;
    
    return true;
}

/**
 * Returns linked list's size (number of items). O(1).
 */
unsigned long linked_list_size(LinkedList *list) {
    return list->size;
}

/**
 * Prints the linked list contents using the provided item printer. O(n).
 */
void linked_list_print(LinkedList *list, void (*print_item)(const void *)) {
    ListItem *item = list->head;

    printf("[");
    while (item != NULL) {
        print_item(item->data);
        if (item->next != NULL) {
            printf(", ");
        }
        item = item->next;
    }
    printf("]\n");
}

/**
 * Free memory allocated by the list. O(n).
 */
void linked_list_destroy(LinkedList *list) {
    ListItem *item = list->head;

    while (item != NULL) {
        ListItem *next = item->next;
        free(item->data);
        item->data = NULL;
        free(item);
        item = next;
    }

    list->head = NULL;
    list->tail = NULL;
}
