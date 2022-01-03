/**-- main.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"

/*-- se completeaza cu definitiile functiilor implementate --*/

void RSD(TArb a)
{
	if(!a) {printf("-"); return;}
	if(!a->st && !a->dr) {printf(" %d ", a->info); return;}
	printf(" %d ", a->info);
	printf("(");
	RSD(a->st);
	printf(",");
	RSD(a->dr);
	printf(")");
}

int main ()
{
	TArb arb;
	TArb arb2;

	randomize();
	do {
		arb = ConstrAA (5, random(3), -50, 50);
		arb2 = ConstrAA (5, random(3), -50, 50);
		AfiArb (arb);
		AfiArb (arb2);
		printf ("noduri: %i   niveluri: %i\n",
			NrNoduri(arb), NrNiv(arb));
		RSD(arb);

		/*-- se completeaza cu apelurile functiilor implementate --*/
		printf("\nProblema 1: %d\n", Numara(arb));
		printf("\nProblema 2: %d\n", Parcurge(arb));

		int max = arb->info;
		Maxim(arb, &max);
		printf("\nProblema 3: %d\n", max);

		printf("\nEl Truco: %d\n", Verifica(arb, arb2));

		DistrArb (&arb);
		printf ("\nInca un arbore ? [D/N] ");

		if (getchar() == 'n') break;
		printf("\n");
	} while (1);

	return 0;
}