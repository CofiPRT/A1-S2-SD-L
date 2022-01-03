/*--- tarb.c --- operatii cu arbori binari --*/
#include "tarb.h"

TArb InitA()         /* initializare arbore */
{
	return NULL;
}

TArb ConstrNod(TInfo x, TArb s, TArb d)/* -> adresa nod (cu informatia x, 
				fiu stanga s, fiu dreapta d) sau NULL in caz de eroare */
{
	TArb aux = (TArb)malloc (sizeof(TNod));  /* incearca alocare spatiu */
	if (!aux) return NULL;                   /* spatiu insuficient */
	aux->info = x; aux->st = s; aux->dr = d; /* actualizeaza campurile nodului */

	return aux;                              /* intoarce adresa nodului */
}

TArb ConstrFr(TInfo x)     /* -> adresa frunza cu informatia x, sau
					NULL daca nu exista spatiu */
{
	TArb aux = (TArb)malloc (sizeof(TNod));
	if (!aux) return NULL;
	aux->info = x; aux->st = aux->dr = NULL;

	return aux;
}

void distruge(TArb r) 	/* functie auxiliara - distruge toate nodurile */
{
	if (!r) return;
	distruge (r->st);     /* distruge subarborele stang */
	distruge (r->dr);     /* distruge subarborele drept */
	free (r);             /* distruge nodul radacina */
}

void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
{
	if (!(*a)) return;       /* arbore deja vid */
	distruge (*a);           /* distruge toate nodurile */
	*a = NULL;               /* arborele este vid */
}

int NrNoduri(TArb r)        /* numarul de noduri din arborele r -*/
{
	if (!r) return 0;          /* arbore vid => 0 noduri */
	return 1 + NrNoduri(r->st) + NrNoduri(r->dr);
}

int NrNiv(TArb r)           /* numar niveluri (0 pentru arbore vid) */
{
	int ns, nd;
	if (!r) return 0;
	ns = NrNiv(r->st); nd = NrNiv(r->dr);
	return 1 + (ns >= nd ? ns : nd);
}

int Numara(TArb arb)
{
	int nr = 0;

	if (!arb)
	{
		return 0;
	}

	int x = (arb->st && arb->info < arb->st->info);

	return x + Numara(arb->st) + Numara(arb->dr);
}

int Parcurge(TArb arb)
{
	if (arb == NULL)
		return 0;

	int s = Parcurge(arb->st);

	int x = (arb->info % 2 == 0) && ((!arb->st && arb->dr) || (arb->st && !arb->dr));

	if (x == 1)
	{
		printf("\tProblema 2 NOD: %d\n", arb->info);
	}

	int d = Parcurge(arb->dr);

	return s + x + d;
}

int Maxim(TArb arb, int *max)
{
	if (!arb)
	{
		return -1;
	}

	int x = arb->info;
	if (x > *max)
		*max = x;

	int max_st = x, max_dr = x;

	Maxim(arb->st, &max_st);
	Maxim(arb->dr, &max_dr);

	if (max_st > *max)
		*max = max_st;

	if (max_dr > *max)
		*max = max_dr;

	return 0;
}

int Verifica(TArb arb1, TArb arb2)
{
	if (!arb1 && !arb2)
		return 0;

	if ((!arb1 && arb2) || (arb1 && !arb2))
		return 1;

	return Verifica(arb1->st, arb2->st) + Verifica(arb1->dr, arb2->dr);
}