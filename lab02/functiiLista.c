/*-- functiiLista.c --*/
#include <ctype.h>
#include "tlista.h"

/*--- operatii de baza pentru lista simplu inlantuita ---*/

TLista AlocCelula(int e)          /* adresa celulei create sau NULL */
{ TLista aux = (TLista)malloc(sizeof(TCelula));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { aux->info = e;                   /* (2,3) completeaza noua celula */
	aux->urm = NULL;
  }
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}

void AfisareL(TLista L)
	   /* afiseaza valorile elementelor din lista */
{
  printf("Lista: [");                      /* marcheaza inceput lista */
  for (; L != NULL; L = L->urm)       /* pentru fiecare celula */
	printf("%d ", L->info);              /* afiseaza informatie */
  printf("]\n");                               /* marcheaza sfarsit lista */
}

void DistrugeL(ALista aL)
{
  TLista aux;
  while(*aL)
  {
	aux = *aL;
	*aL = aux->urm;
	free(aux);
  }
}

int PerechiL(TLista L)
{
	int nr = 0, index = 1;
	while(L != NULL && L->urm != NULL)
	{
		if(L->info % 2 == L->urm->info % 2)
		{
			nr++;
			printf("(%d, %d): %d, %d\n", index, index + 1, L->info, L->urm->info);
		}
		L = L->urm;
		index++;
	}

	return nr;
}

int JumatateL(TLista L)
{
	int nr1 = 0, nr2 = 0;
	TLista m = L;
	TLista L2 = L;
	while (L2 != NULL)
	{
		m = m->urm;
		L2 = L2->urm;
		if(L2);
		L2 = L2->urm;
	}

	while (L != m)
	{
		if (L->info % 2)
		{
			nr1++;
		}
		L = L->urm;
	}

	while(m != NULL)
	{
		if (m->info % 2)
		{
			nr2++;
		}
		m = m->urm;
	}
	
	return nr1 == nr2;
}

int SameL(TLista A, TLista B)
{
	TLista B2 = B;
	for (; A != NULL; A = A->urm)
	{
		for (B2 = B; B2 != NULL; B2 = B2->urm)
		{
			if (A->info == B2->info)
			{
				break;
			}
		}
		if (B2 == NULL)
		{
			return 0;
		}
	}

	return 1;
}

int BonusL(TLista L, int el)
{
	int ins = 0;
	TLista El;

	for(; L != NULL; L = L->urm)
	{
		if (!L) return 0;
		if (L->info == el)
		{
			El = AlocCelula(el);
			if (!El)
			{
				return 0;
			}
			else
			{
				El->urm = L->urm;
				L->urm = El;
				L = L->urm;
			}
			ins++;
		}
	}

	return ins;
}

TLista Muta(ALista aL, int *dim)
{
	TLista newL = NULL, aux, ant, L = *aL, auxL = NULL;
	*dim = 0;
	int i = 1;
	while(L)
	{
		if (i % 2 && !(L->info % 2))
		{
			TLista aux = L;
			if(!aux)
			{
				*aL = aux -> urm;
				L = L->urm;
				aux->urm = NULL;
			}
			else
			{
				ant->urm = L->urm;
				L = L->urm;
				aux->urm = NULL;
			}
			if (!newL)
			{
				auxL = aux;
				newL = aux;
			}
			else
			{
				auxL->urm = aux;
				auxL = auxL->urm;
			}
			(*dim)++;
		}
		else
		{
			ant = L;
			L = L->urm;
			i++;
		}

	}
	return newL;
}

int prim(int x)
{
	if (x == 0 || x == 1)
		return 0;
	int i;
	for (i = 2; i <= x/2; i++)
		if (!(x % i))
			return 0;
	return 1;
}

TLista Copie(TLista L, int *dim)
{
	TLista newL = NULL, auxL = NULL;

	while(L)
	{
		if (prim(L->info))
		{
			TLista aux = AlocCelula(L->info);
			if (!newL)
			{
				newL = aux;
				auxL = aux;
			}
			else
			{
				auxL->urm = aux;
				auxL = auxL->urm;
			}
			(*dim)++;
		}
		L = L->urm;
	}
	return newL;
}

TLista Maxime(TLista L1, TLista L2)
{
	TLista newL = NULL, auxL = NULL;

	while (L1 && L2)
	{
		TLista aux = AlocCelula(L1->info >= L2->info ? L1->info : L2->info);
		if(!newL)
		{
			newL = aux;
			auxL = aux;
		}
		else
		{
			auxL->urm = aux;
			auxL = auxL->urm;
		}
		L1 = L1->urm;
		L2 = L2->urm;
	}
	TLista x = (L1 ? L1 : L2);
	while (x)
	{
		TLista aux = AlocCelula(x->info);
		if(!newL)
		{
			newL = aux;
			auxL = aux;
		}
		else
		{
			auxL->urm = aux;
			auxL = auxL->urm;
		}
		x = x->urm;
	}

	return newL;
}

void Bonus(ALista aL, TLista L2)
{
	TLista aux, ant = NULL, L1 =*aL;
	while(L1 && L2)
	{
		if (L1->info > L2->info)
		{
			if(!ant)
			{
				aux = L2;
				L2 = L2->urm;
				aux->urm = L1;
				*aL = aux;
			}
			else
			{
				aux = L2;
				L2 = L2->urm;
				aux->urm = L1;
				ant->urm = aux;
			}
		}
		if (L1->info < L2->info)
		{
			ant = L1;
			L1 = L1 -> urm;
		}
		if (L1->info == L2->info)
		{
			L1 = L1->urm;
			L2 = L2->urm;
		}

	}
	aux = *aL;
	AfisareL(aux);
}

void inserareOrdonata(ALista aL, TLista aux) {
	TLista L = *aL;
	TLista ant = NULL;

	while (L != NULL
		&& (strcmp(L->info->nume, aux->info->nume) < 0
			|| (!strcmp(L->info->nume, aux->info->nume)
				&& strcmp(L->info->prenume, aux->info->prenume) < 0)))
	{
		ant = L;
		L = L->urm;
	}

	if (ant == NULL)
	{
		*aL = aux;
		aux->urm = L;
	}
	else
	{
		ant->urm = aux;
		aux->urm = L;
	}
}

while(L != NULL)
	{
		if (L->info->notaSD >= 5 && L->info->notaPC < 5)
		{
			TLista aux = L;
			if(!aux)
			{
				*aL = aux -> urm;
				L = L->urm;
				aux->urm = NULL;
			}
			else
			{
				ant->urm = L->urm;
				L = L->urm;
				aux->urm = NULL;

			}
			if (!L_new)
			{
				L_aux = aux;
				L_new = aux;
			}
			else
			{
				
				L_aux->urm = aux;
				L_aux = L_aux->urm;
			}
			(*elem_mut)++;
		}
		else
		{
			ant = L;
			L = L->urm;
			(*elem_ram)++;
		}
	}