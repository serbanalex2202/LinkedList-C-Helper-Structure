/*
 * Author: Serban Alexandru
 *
 * LinkedList structure
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/**
 *  Element structure
 */

/**
 * Nod structure
 */
typedef struct Nod {
	void* item;
	struct Nod* next;
	struct Nod* prev;

} Nod;

/**
 * LinkedList structure.
 * The structure contains the head of the list, the tail the size and the related methods.
 */
typedef struct LinkedList {

	Nod* head;
	Nod* tail;
	int size;

	void (*addFirst)(struct LinkedList*, void*, size_t);
	void * (*popFirst)(struct LinkedList*);
	void * (*showFirst)(struct LinkedList*);

	void (*addLast)(struct LinkedList*, void*, size_t);
	void * (*showLast)(struct LinkedList*);
	void * (*popLast)(struct LinkedList*);

	void (*display)(struct LinkedList*, void(void*));
	void (*displayR)(struct LinkedList*, void(void*));

	int (*contains)(struct LinkedList*, void *, int(void*, void*));

	int (*removeFirstOcc)(struct LinkedList*, void*, int(void*, void*),
			void(void*));
	int (*removeLastOcc)(struct LinkedList*, void*, int(void*, void*),
			void(void*));

	int (*removeAllOcc)(struct LinkedList*, void*, int(void*, void*),
			void(void*));

	void (*freeMem)(struct LinkedList*, void(void*));

} LinkedList;

/**
 * Adds new element at the beginning of the list and allocate memory.
 */
void addFirst(LinkedList* list, void* item, size_t dim) {

	Nod* n = (Nod*) malloc(sizeof(Nod));
	n->item = (void *) calloc(1, dim);
	memmove(n->item, item, dim);
	n->next = NULL;
	n->prev = NULL;

	if (list->tail == NULL) {
		list->tail = n;
	} else {
		list->head->prev = n;
		n->next = list->head;
	}
	list->head = n;
	list->size++;
}

/*
 * Returns the first element and removes it from the list.
 * The element must be freed afterwards.
 */
void * popFirst(LinkedList* list) {

	Nod* head = list->head;
	void* item = head->item;

	list->head = head->next;
	list->head->prev = NULL;
	list->size--;

	free(head);
	return item;
}

/*
 * * Only returns the first element without removing it from the list
 */
void * showFirst(LinkedList* list) {
	Nod* head = list->head;
	return head->item;
}

/**
 * Adds new item at the end of the list
 */
void addLast(LinkedList* list, void * item, size_t dim) {

	Nod* n = (Nod*) malloc(sizeof(Nod));
	n->item = calloc(1, dim);
	memmove(n->item, item, dim);
	n->next = NULL;
	n->prev = NULL;

	if (list->head == NULL) {
		list->head = n;

	} else {
		list->tail->next = n;
		n->prev = list->tail;
	}
	list->tail = n;
	list->size++;
}

/**
 * Returns the last element and removes it form the list.
 * The element must be freed until the end of the program.
 */
void* popLast(LinkedList* list) {

	Nod* tail = list->tail;
	void* item = tail->item;

	list->tail = tail->prev;
	list->tail->next = NULL;

	list->size--;

	free(tail);
	return item;
}

/**
 * Only returns the last element without removing it from the list
 */
void* showLast(LinkedList* list) {
	Nod* tail = list->tail;
	return tail->item;
}

/**
 *  Prints list with given print function
 */
void display(LinkedList* list, void (*show)(void*)) {
	printf("List :\n");
	if (list->size == 0)
		printf("Empty LinkedList");
	else {
		Nod* head = list->head;
		int i, size = list->size;

		for (i = 0; i < size; i++) {
			(*show)(head->item);
			head = head->next;
		}
	}
	printf("\n");
}

/**
 * Reverse print of elements (done for testing links)
 */
void displayR(LinkedList* list, void (*show)(void*)) {
	printf("ListaR :\n");
	if (list->size == 0)
		printf("Empty LinkedList");
	else {
		Nod* tail = list->tail;
		int i, size = list->size;

		for (i = 0; i < size; i++) {
			(*show)(tail->item);
			tail = tail->prev;
		}
	}
	printf("\n");
}

/*
 * Verify if List contains given item and returns 1 or 0 if it doesn't
 */
int contains(LinkedList* list, void * elem, int (*comp)(void*, void *)) {

	if (list->size == 0) {
		return 0;
	} else {
		Nod* head = list->head;
		int i, size = list->size;

		for (i = 0; i < size; i++) {
			if (comp(elem, head->item) == 0) {
				return 1;
			}
			head = head->next;
		}
	}

	return 0;
}

/*
 * Remove the last occurrence of given item, free memory and returns 1 or 0 if item wasn't found
 */
int removeLast(LinkedList* list, void * item2, int (*comp)(void*, void *),
		void (*myfree)(void*)) {

	if (list->size == 0) {
		return 0;/* Nothing to remove*/
	}

	Nod* current = list->tail;

	while (1) {
		if (comp(item2, current->item) == 0) {

			/* Rebuild links considering the removal of leading or trailing nodes*/
			if (current->prev != NULL) {
				current->prev->next = current->next;
			} else {
				list->head = current->next;
			}

			if (current->next != NULL) {
				current->next->prev = current->prev;
			} else {
				list->tail = current->prev;
			}

			/* Free removed node*/
			myfree(current->item);
			free(current);

			list->size--;
			return 1;
		}

		current = current->prev;
		if (current == NULL) {
			break;
		}
	}
	return 0;

}

/**
 * Remove All occurrences of given item and free memory for each removed node.
 * The removal is done by traversing the list.
 */
int removeAll(LinkedList* list, void * item2, int (*comp)(void*, void *),
		void (*myfree)(void*)) {

	int occs = 0;

	if (list->size == 0) {
		return 0; /* Nothing to remove*/
	}

	Nod * current = list->head;
	Nod * next;

	while (1) {
		next = current->next;
		if (comp(item2, current->item) == 0) {

			/* Rebuild links considering the removal of leading or trailing nodes*/
			if (current->prev != NULL) {
				current->prev->next = current->next;
			} else {
				list->head = current->next;
			}

			if (current->next != NULL) {
				current->next->prev = current->prev;
			} else {
				list->tail = current->prev;
			}

			/* Free memory for each removed element*/
			myfree(current->item);
			free(current);

			list->size--;
			occs++;

		}

		current = next;
		if (current == NULL) {
			break;
		}
	}

	return occs;
}

/*
 * Remove first occurrence of given element and free the memory.
 */
int removeFirst(LinkedList* list, void * item2, int (*comp)(void*, void *),
		void (*myfree)(void*)) {

	if (list->size == 0) {
		return 0; /* Nothing to remove */
	}

	Nod* current = list->head;

	while (1) {
		if (comp(item2, current->item) == 0) {

			/* Rebuild links considering leading and trailing nodes*/
			if (current->prev != NULL) {
				current->prev->next = current->next;
			} else {
				list->head = current->next;
			}

			if (current->next != NULL) {
				current->next->prev = current->prev;
			} else {
				list->tail = current->prev;
			}

			/* Free removed node*/
			myfree(current->item);
			free(current);

			list->size--;
			return 1;
		}
		current = current->next;
		if (current == NULL) {
			break;
		}
	}
	return 0;

}

/*
 * Free memory of each element and LinkedList memory
 */
void freeMem(LinkedList* list, void (*myfree)(void*)) {

	if (list->size == 0) {
		return;
	}

	Nod * current = list->head;
	Nod * next = current->next;

	while (1) {

		myfree(current->item);
		free(current);
		current = next;
		if (current == NULL) {
			break;
		}
		next = current->next;
	}
}

/**
 * LinkedList constructor function
 */
LinkedList crLinkedList() {

	LinkedList list;
	list.size = 0;

	list.head = NULL;
	list.tail = NULL;

	list.addFirst = &addFirst;
	list.popFirst = &popFirst;
	list.showFirst = &showFirst;

	list.showLast = &showLast;
	list.addLast = &addLast;
	list.popLast = &popLast;

	list.display = &display;
	list.displayR = &displayR;

	list.contains = &contains;
	list.removeFirstOcc = &removeFirst;
	list.removeLastOcc = &removeLast;
	list.removeAllOcc = &removeAll;

	list.freeMem = &freeMem;
	return list;
}
