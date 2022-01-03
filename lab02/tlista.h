/*-- tlista.h --- LISTA SIMPLU INLANTUITA cu elemente de tip intreg ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#ifndef _LISTA_SIMPLU_INLANTUITA_
#define _LISTA_SIMPLU_INLANTUITA_

typedef struct celula
{ int info;
  struct celula * urm;
} TCelula, *TLista, **ALista; /* tipurile Celula, Lista si Adresa_Lista */

#define VidaL(L) ((L) == NULL)

/*-- operatii elementare --*/

TLista AlocCelula(int);          /* adresa celulei create sau NULL */
void   DistrugeL (ALista);       /* elimina toate celulele din lista */

void AfisareL (TLista L);

int PerechiL(TLista L);

int JumatateL(TLista L);

int SameL(TLista A, TLista B);

int BonusL(TLista L, int el);

TLista Muta(ALista aL, int *dim);

TLista Copie(TLista L, int *dim);

TLista Maxime(TLista L1, TLista L2);

void Bonus(ALista aL, TLista L2);

#endif