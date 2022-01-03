/*--- graf-M.c --- Graf implementat cu Matrice de adiacente --*/
#include "graf-M.h"
#include <string.h>

void* AlocG(int nr)
{ int i;
  AGM g = (AGM)malloc (sizeof(TGM));              /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (int*)malloc(nr * nr * sizeof(int)); /* matrice liniarizata */
  if (!g->x) { free(g); return NULL; }
  for (i = 0; i < nr * nr; i++)
    g->x[i] = ArcInex;
  g->n = nr;
  return (void*)g;
}


void DistrG(void** ag)
{ free (((AGM)(*ag))->x);
  free(*ag);
  * ag = NULL;
}


int CostArc(void* g, int s, int d)
{ 
  /* functia intoarce costul arcului (s, d); daca arcul nu exista intoarce ArcInex */
  AGM graf = (AGM)g;
  
  int val = graf->x[(s - 1) * graf->n + (d - 1)];
  return val ? val : ArcInex;
}

int Grad_Iesire(void *g, int nod)
{
  AGM graf = (AGM)g;
  int grad = 0;

  int i;
  for (i = 0; i < graf->n; i++)
  {
    if (graf->x[(nod - 1) * graf->n + i])
    {
      grad++;
    }
  }

  return grad;
}

int Ultim_adiacent(void *g, int nod)
{
  AGM graf = (AGM)g;
  int ult = 0;

  int i;
  for (i = 0; i < graf->n; i++)
  {
    if (graf->x[(nod - 1) * graf->n + i])
    {
      ult = i + 1;
    }
  }

  return ult;
}

int ArcMax(void *g, int *s, int *d)
{
  AGM graf = (AGM)g;

  int max = 0;
  int i, j;

  for (i = 0; i < graf->n; i++)
  {
    for (j = 0; j < graf->n; j++)
    {
      if (graf->x[i * graf->n + j] >= max)
      {
        *s = i + 1;
        *d = j + 1;
        max = graf->x[i * graf->n + j];
      }
    }
  }

  return max;
}

int NrNoduri(void* g)
{
    return ((AGM)g)->n;
}

int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  int i, j, n;
  int x;
  AGM g;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen(numefis, "rt");
  if (!f) return -2;
  if (!fscanf(f, "%i", &n) || n <= 0) return -3;
  *ag = g = (AGM)AlocG(n);
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &i, &j, &x) == 3)
  { if (i < 1 || i > n || j < 1 || j > n)
    { fclose(f); return -4;}
      ((AGM)g)->x[(i-1)*((AGM)g)->n + j-1] = x;
  }
  fclose(f);
  return 1;
}

