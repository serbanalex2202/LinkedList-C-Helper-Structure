#include "LinkedList.h"

void afis(void * item) {
	printf("%d ", *((int*) item));
}

int compare(void * item1, void * item2) {
	if ((*((int*) item1)) > (*((int*) item2))) {
		return 1;
	}
	if ((*((int*) item1)) == (*((int*) item2))) {
		return 0;
	}
	return -1;
}

void freeItem(void * item) {
	free(item);
}

int main() {
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	int x = 40;

	/*
	 * Apeluri :
	 * 	lista.addLast(&lista, &a, sizeof(a));
	 * 	lista.display(&lista, afis);
	 * 	lista.removeFirstOcc(&lista, &a , compare , freeItem);
	 *
	 */

	LinkedList lista = crLinkedList();
	lista.addLast(&lista, &a, sizeof(a));
	lista.addLast(&lista, &b, sizeof(b));
	lista.addLast(&lista, &a, sizeof(c));

	lista.addLast(&lista, &c, sizeof(a));
	lista.addLast(&lista, &a, sizeof(b));
	lista.addLast(&lista, &d, sizeof(c));
	////////////////////////////////////////////
	printf("1 ");
	lista.display(&lista, afis);

	lista.removeFirstOcc(&lista, &a, compare, freeItem);
	lista.removeLastOcc(&lista, &a, compare, freeItem);
	printf("2 remove first and last ");
	lista.display(&lista, afis);

	/////////////////////////////////

	lista.addLast(&lista, &c, sizeof(a));
	lista.addLast(&lista, &a, sizeof(b));
	lista.addLast(&lista, &d, sizeof(c));
	lista.addLast(&lista, &a, sizeof(b));
	printf("3 ");
	lista.display(&lista, afis);
	lista.removeAllOcc(&lista, &a, compare, freeItem);
	printf("4 remove all occs ");
	lista.display(&lista, afis);
	////////////////////////////////////
	lista.freeMem(&lista, freeItem);
	return 0;

}
