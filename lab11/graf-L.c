/*--- graf-L.c --- Graf implementat cu liste --*/
#include "graf-L.h"

void* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  AGL g = (AGL)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->n = nr;
  return (void*)g;
}

void DistrG(void** ag)
{ int i;
  AArc p, aux;
  for(i = 1; i < NrNoduri(*ag); i++)
  { p = ((AGL)(*ag))->x[i];
    while(p)
    { aux = p; p = p->urm;
      free(aux);
    }
  }
  free(((AGL)(*ag))->x);
  free(*ag);
  *ag = NULL;
}


int CostArc(void* g, int s, int d)
{   /* intoarce costul arcului (s, d); daca arcul nu exista intoarce ArcInex */
    AGL graf = (AGL)g;

    AArc L = graf->x[s];
    while (L)
    {
      if (L->d == d)
      {
        return L->c;
      }
      L = L->urm;
    }
    return ArcInex;
}

int Grad_Iesire(void *g, int nod)
{
  AGL graf = (AGL)g;

  AArc L = graf->x[nod];
  int grad = 0;

  while (L)
  {
    grad++;
    L = L->urm;
  }

  return grad;
}

int Ultim_adiacent(void *g, int nod)
{
  AGL graf = (AGL)g;

  AArc L = graf->x[nod];
  int ult = 0;

  while (L)
  {
    ult = L->d;
    L = L->urm;
  }

  return ult;
}

int ArcMax(void *g, int *s, int *d)
{
  AGL graf = (AGL)g;

  int max = 0;
  int i;
  for (i = 1; i <= graf->n; i++)
  {
    AArc L = graf->x[i];

    while (L)
    {
      if (L->c >= max)
      {
        *s = i;
        *d = L->d;
        max = L->c;
      }
      L = L->urm;
    }
  }

  return max;
}

int NrNoduri(void* g)
{ return ((AGL)(g))->n; }



int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  AGL g;
  int s, d;
  int x;
  AArc *p, aux;
  int n;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen (numefis, "rt");
  if (!f) return -2;
  if (!fscanf (f, "%i", &n) || n <= 0) return -3;
  *ag = AlocG(n);
  g = *(AGL*)ag;
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &s, &d, &x) == 3)
  { if (s < 1 || s > n || d < 1 || d > n)
    { fclose(f); return -4;}
    p = g->x + s;
    while (*p && (*p)->d < d) p = &(*p)->urm;
    aux = (TCelArc*)calloc(sizeof(TCelArc),1);
    if (!aux) return -2;                     /* criza spatiu */
    aux->urm = *p; *p = aux;
    aux->d = d; aux->c = x;
  }
  fclose(f);
  return 1;
}

