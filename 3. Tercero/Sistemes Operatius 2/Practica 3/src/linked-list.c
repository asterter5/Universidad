/**
 *
 * Linked-list implementation.
 *
 * This is an implementation of a simple linked-list. A minimal
 * set of necessary functions have been included.
 *
 * Lluis Garrido, 2016.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * We include the linked-list.h header. Note the double
 * quotes.
 */

#include "linked-list.h"

/**
 *
 * Free data element. The user should adapt this function to their needs.  This
 * function is called internally by deleteList.
 *
 */

static void freeListData(ListData *data) {
    free(data->totalRetrasos);
    free(data->numeroRetrasos);
    free(data->key);
    free(data->key_sec);
    free(data);
}

/**
 *
 * Dumps data contents to stdout. To be used for debugging.
 *
 */

static void dumpListData(ListData *data) {
    if (data == NULL) return;

    printf("Key %s\n", data->key);
    printf(
            "Dilluns: %i Dimarts: %i Dimecres: %i  Dijous: %i Divendres: %i Dissabte: %i Diumenge: %i\n\n",
            data->totalRetrasos[0], data->totalRetrasos[1],
            data->totalRetrasos[2], data->totalRetrasos[3],
            data->totalRetrasos[4], data->totalRetrasos[5],
            data->totalRetrasos[6]);
}

/**
 *
 * Compares if key1 is equal to key2. Should return 1 (true) if condition
 * is satisfied, 0 (false) otherwise.
 *
 */

static int compEQ(TYPE_LIST_KEY key1, TYPE_LIST_KEY key2) {
    int rc = 0;
    if (strcmp(key1, key2) == 0) rc = 1;
    return rc;
}

/**
 *
 * NO CANVIEU EL CODI QUE HI HA A SOTA LLEVAT QUE SAPIGUEU EL QUE ESTEU FENT.
 * PER FER LES PRACTIQUES NO CAL MODIFICAR EL CODI QUE HI HA A SOTA.
 *
 */

/**
 *
 * Initialize an empty list
 *
 */

void initList(List *l) {
    l->numItems = 0;
    l->first = NULL;
}

/**
 *
 * Insert data in the list.  This function does not perform a copy of data
 * when inserting it in the list, it rather creates a list item and makes
 * this item point to the data. Thus, the contents of data should not be
 * overwritten after calling this function.
 *
 */

void insertList(List *l, ListData *data) {
    ListItem *tmp, *x;

    x = malloc(sizeof (ListItem));

    if (x == 0) {
        printf("insufficient memory (insertItem)\n");
        exit(1);
    }

    /* Insert item at first position */

    tmp = l->first;
    l->first = x;
    x->next = tmp;

    /* Link data to inserted item */
    x->data = data;

    l->numItems++;
}

/**
 *
 * Find item containing the specified key and subkey. Returns the data
 * that it points to (not the item itself).
 *
 */

ListData *findList_2k(List *l, TYPE_LIST_KEY key, TYPE_LIST_KEY key_sec) {
    ListItem *current;

    current = l->first;

    while (current != NULL) {
        if (compEQ(current->data->key, key) && (compEQ(current->data->key_sec, key_sec)))
            return (current->data);

        current = current->next;
    }

    return (NULL);
}

/**
 *
 * Find item containing the specified key. Returns the data
 * that it points to (not the item itself).
 *
 */

ListData *findList(List *l, TYPE_LIST_KEY key) {
    ListItem *current;

    current = l->first;

    while (current != NULL) {
        if (compEQ(current->data->key, key))
            return (current->data);

        current = current->next;
    }

    return (NULL);
}

/**
 *
 * Deletes the first item of the list. The data to which
 * the deleted item points to also is deleted.
 *
 */

void deleteFirstList(List *l) {
    ListItem *tmp;

    tmp = l->first;

    if (tmp) {
        l->first = tmp->next;
        freeListData(tmp->data);
        free(tmp);
        l->numItems--;
    }
}

/**
 *
 * Deletes a list including the data to which their
 * items point to.
 *
 */

void deleteList(List *l) {
    ListItem *current, *next;

    current = l->first;

    while (current != NULL) {
        next = current->next;
        freeListData(current->data);
        free(current);
        current = next;
    }

    l->numItems = 0;
    l->first = NULL;
}

/**
 *
 * Dumps the contents of the list. Internally this function
 * called dumpListData which is user defined.
 *
 */

void dumpList(List *l) {
    ListItem *current;

    current = l->first;

    while (current != NULL) {
        dumpListData(current->data);
        current = current->next;
    }

    printf("Total number of items: %d\n", l->numItems);
}

int listLength(List *l) {
    ListItem *current;
    int count;

    current = l->first;
    count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
