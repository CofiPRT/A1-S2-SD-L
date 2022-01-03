/*--- lista2.c ---
      operatii lista generica dublu inlantuita, circulara, cu santinela ---*/

#include "lista2.h"

int InsDupa(TLDI a, void* x)  /* inserare dupa celula cu adresa a -> 1/0 */
{
	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
	if(!aux) return 0;
	aux->info = x;
	aux->ant = a;
	aux->urm = a->urm;
	a->urm->ant = aux;
	a->urm = aux;
    return 1;
}


void ResetLDI(TLDI s)
     /* transforma lista in lista vida */
{
	TLDI p = s->urm, aux;
	while(p != s)
	{
		aux = p;
		p = p->urm;
		free(aux->info);
		free(aux);
	}
	s->urm = s->ant = s;
}

void DistrLDI(TLDI* as)
     /* elibereaza tot spatiul ocupat de lista, inclusiv santinela */
{
	ResetLDI(*as);
	free(*as);
	*as = NULL;
}

TLDI InitLDI()
    /* -> lista vida, cu info din santinela specifica aplicatiei */
{
	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
    if (!aux) return NULL;

	aux->ant = aux->urm = aux;
    aux->info = NULL;

	return aux;     /* rezultatul este adresa santinelei sau NULL */
}

void AfisareLDI(TLDI s, void (*afiEl)(void *))
    /* afisare lista */
{
	TLDI p;
	printf("Lista: ");
	if(s->urm == s)
	{
		printf("vida\n");
		return;
	}
	for(p = s->urm; p != s; p = p->urm)
		afiEl(p->info);
	printf("\n");
}

TLDI Prob1(TLDI L)
{
	TLDI fw = L->urm;
	TLDI bw = L->ant;
	TLDI s = L;

	TLDI new_L = InitLDI();

	while (fw != bw && bw->urm != fw)
	{
		if (*((int*)(fw->info)) % 2 == 0)
		{
			InsDupa(new_L->ant, fw->info);
		}
		fw = fw->urm;
		bw = bw->ant;
	}

	return new_L;
}

TLDI Prob2(TLDI L)
{
	TLDI s = L;
	TLDI p = L->urm;

	while (p->info)
	{
		TLDI next = p->urm;
		while (next != s)
		{
			if (*((int*)p->info) == *((int*)next->info))
			{
				next->ant->urm = next->urm;
				next->urm->ant = next->ant;
			}

			next = next->urm;
		}

		p = p->urm;
	}
}

TLDI Bonus(TLDI L, int k)
{
	TLDI s = L;
	TLDI first = L->urm;
	TLDI last = L->ant;

	TLDI curr = L->urm;
	while (k)
	{
		curr = curr->urm;
		k--;
	}

	s->urm = curr;
	s->ant = curr->ant;

	curr->ant->urm = s;
	curr->ant = s;

	first->ant = last;
	last->urm = first;


}