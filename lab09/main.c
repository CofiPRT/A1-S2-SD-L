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

int CautareMare(TArb a, int x)
{
	if (!a)
	{
		return 0;
	}
	if (a->info < x)
	{
		return CautareMare(a->st, x) + CautareMare(a->dr, x);
	}
	
	printf("Nod: %d\n", a->info);
	return 1 + CautareMare(a->dr, x);
}

TArb Succesor(TArb a, int *nivel)
{
	int rad = a->info;

	if (!a->dr)
	{
		*nivel = -1;
		return NULL;
	}

	TArb curent = a->dr;
	*nivel = 2;

	while (curent)
	{
		if (!curent->st)
		{
			return curent;
		}
		(*nivel)++;
		curent = curent->st;
	}
}

void Duplica(TArb a)
{
	if (!a)
		return;
	if (a->info % 2 == 0)
	{
		TArb new = ConstrNod(a->info, a->st, NULL);
		a->st = new;
		Duplica(new->st);
		Duplica(a->dr);
	}
	else
	{
		Duplica(a->st);
		Duplica(a->dr);
	}
}

int Verifica(TArb a, int nivel, int *nivel_fr) 
{
	if (!a)
		return 1;

	if (!a->st && !a->dr) 
	{ 
		if (*nivel_fr == 1) 
		{ 
			*nivel_fr = nivel;
			return 1;
		}

		if (nivel == *nivel_fr)
			return 1;
		else
			return 0;
	} 
  	
  	nivel++;
	return Verifica(a->st, nivel, nivel_fr) * Verifica(a->dr, nivel, nivel_fr);
}

int Verifica2(TArb a)
{
	int nivel_fr = 1;
	if (Verifica(a, 1, &nivel_fr))
	{
		return nivel_fr;
	}
	return -1;
}


TArb CitesteABC(int n) {
	TArb arb = NULL;

	int x;
	while (scanf("%d", &x) == 1) {
		if (arb == NULL) {
			arb = ConstrFr(x);
		} else {
			int niv = 0;
			TArb arb_aux = arb;
			TArb p = NULL;

			while (arb_aux != NULL) {
				if (arb_aux->info < x) {
					p = arb_aux;
					arb_aux = arb_aux->dr;
				} else if (arb_aux->info >= x) {
					p = arb_aux;
					arb_aux = arb_aux->st;
				}
				niv++;
			}

			if (niv < n) {
				if (p->info < x)
					p->dr = ConstrFr(x);
				else
					p->st = ConstrFr(x);
			}
		}
	}

	return arb;
}

int main ()
{
	printf("Introduceti valorile nodurilor din arbore terminate cu o valoare nenumerice\n");
	TArb arb = CitesteABC(5);
	AfiArb(arb);
	printf ("noduri: %i   niveluri: %i\n",	NrNoduri(arb), NrNiv(arb));
	RSD(arb);
	printf("\n");

	/*-- se completeaza cu apelurile functiilor implementate --*/
	int p1 = CautareMare(arb, 5);
	printf("Probl1: %d\n", p1);

	int nivel;
	TArb p2 = Succesor(arb, &nivel);
	if (!p2)
	{
		printf("Probl2: Nod: NULL Nivel: -1\n");
	}
	else
	{
		printf("Probl2: Nod: %d Nivel: %d\n", p2->info, nivel);
	}
	

	Duplica(arb);
	AfiArb(arb);

	int p4 = Verifica2(arb);
	printf("Probl4: %d\n", p4);

	DistrArb (&arb);
	return 0;
}
