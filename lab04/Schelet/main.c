#include "THeader.h"

int main() {
	int n;

	printf("Numar studenti: ");
	scanf("%d", &n);

	TLista listaStudenti = initializareListaStudenti(n);
	if (!listaStudenti)
		return -1;

	AfisareStudenti(listaStudenti);

	printf("Problema 2:\n");

	int elem_mut, elem_ram;
	TLista L_new = Probl2(&listaStudenti, &elem_mut, &elem_ram);

	AfisareStudenti(listaStudenti);
	AfisareStudenti(L_new);
	printf("Elemente mutate: %d\nElemente ramase: %d\n", elem_mut, elem_ram);


	// Apeluri functii laborator

	return 0;
}
