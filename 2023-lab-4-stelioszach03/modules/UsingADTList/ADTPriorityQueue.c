///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Priority Queue μέσω ταξινομημένης λίστας.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTList.h"			// Η υλοποίηση του PriorityQueue χρησιμοποιεί List


// Ενα PriorityQueue είναι pointer σε αυτό το struct
struct priority_queue {
	List list;		
	CompareFunc compare;
};



// Βοηθητικές συναρτήσεις //////////////////////////////////////////////////////////////////

// Αρχικοποιεί την ταξινομημένη λίστα από τα στοιχεία του vector values.

static void naive_initialize_list(PriorityQueue pqueue, Vector values, CompareFunc compare) {
    int size = vector_size(values);
    for (int i = 0; i < size; i++) {
        list_insert_next(pqueue->list, LIST_BOF, vector_get_at(values, i));
    }
    list_sort(pqueue->list, compare); // Compare is now a valid argument
}



// Συναρτήσεις του ADTPriorityQueue ////////////////////////////////////////////////////////

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
    PriorityQueue pqueue = malloc(sizeof(*pqueue));
    pqueue->list = list_create(destroy_value);
    pqueue->compare = compare;
	// Για την κλήση της συνάρτησης destroy_value, την περνάμε απλά στη list_create
	// οπότε θα καλείται αυτόματα όταν το στοιχείο αφαιρεθεί από τη λίστα.
	pqueue->list = list_create(destroy_value);
	// ...

	// Αν values != NULL, αρχικοποιούμε την ταξινομημένη λίστα.
    if (values != NULL)
    naive_initialize_list(pqueue, values, compare);

	return pqueue;
}

int pqueue_size(PriorityQueue pqueue) {
   return list_size(pqueue->list);
}


Pointer pqueue_max(PriorityQueue pqueue) {
	return list_node_value(pqueue->list, list_last(pqueue->list));
}

void pqueue_insert(PriorityQueue pqueue, Pointer value) {
   ListNode node = list_first(pqueue->list);
   while (node != LIST_EOF && pqueue->compare(list_node_value(pqueue->list, node), value) < 0)
       node = list_next(pqueue->list, node);;
   list_insert_next(pqueue->list, node, value);
}


void pqueue_remove_max(PriorityQueue pqueue) {
   list_remove_next(pqueue->list, list_last(pqueue->list));
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	// Απλά καλούμε την αντίστοιχη συνάρτηση της λίστας
	return list_set_destroy_value(pqueue->list, destroy_value);
}

void pqueue_destroy(PriorityQueue pqueue) {
	list_destroy(pqueue->list);
   free(pqueue);

}
