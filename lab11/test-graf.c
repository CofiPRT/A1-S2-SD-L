/*--- test-graf.c ---*/
#include "graf.h"

void AfiM(void* g)
{ int i,j,k, n = NrNoduri(g);
  for (i = 1; i <= n; i++)
  { for (j = 1; j <= n; j++)
    { k = CostArc(g,i,j);
      if(k == ArcInex) printf("  - ");
      else printf("%3i ", k);
    }
    printf("\n");
  }
}

int main()
{
  void* g;

  if (CitGraf(&g) <= 0)
  { printf("-=- eroare la citire -=-\n"); return -1;}
  printf(" -=- graf cu %i noduri -=-\n", NrNoduri(g));
  AfiM(g);

  /*-- apel functii definite --*/
  int s = 0, d = 0;

  printf("Cost Arc: %d\n", CostArc(g, 3, 2));
  printf("Grad Iesire: %d\n", Grad_Iesire(g, 3));
  printf("Ultim Adiancent: %d\n", Ultim_adiacent(g, 3));
  printf("Arc Max: %d\n", ArcMax(g, &s, &d));

  DistrG(&g);
  return 0;
}
