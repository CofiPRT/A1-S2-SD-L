/*--- TestLista.c ---*/
#include <ctype.h>
#include <stdio.h>
#include "tlista.h"

TLista CitireL(size_t *lg)     /* construieste lista cu elemente citite */
{ TLista L = NULL, u, aux;
  int x;
  char ch;
  for(*lg = 0; scanf("%i", &x) == 1; )
  {
	aux = AlocCelula(x);           /* incearca inserarea valorii citite */
	if(!aux) return L;              /* alocare esuata => sfarsit citire */
	if(L == NULL) L = aux;
	else u->urm = aux;
	u = aux;
	(*lg)++;
  }

  while((ch=getchar()) != EOF && ch != '\n');
  return L;                     /* intoarce lista rezultat */
}

int main ()
{
	TLista x = NULL;     /* Lista prelucrata */
  	size_t lx;           /* lungime lista */

  	TLista x2 = NULL;
  	size_t lx2;

  for (;;)
  {
	/* citeste si afiseaza lista */
	printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
	x = CitireL(&lx);
	AfisareL(x);
	if(!x) continue;

	printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
	x2 = CitireL(&lx2);
	AfisareL(x2);
	if(!x2) continue;


	/* apeluri functii implementate */
	int dim;
	Bonus(&x, x2);
	printf("Bonus: ");
	


	DistrugeL(&x);
	DistrugeL(&x2);
	printf ("\n  Inca un test ? [d/n]");
	if (getchar() == 'n') break;
  }
}