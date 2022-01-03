/*-- heap.c --*/
#include "heap.h"

#define NMAX 25
static char desen[20][81], cri[] = "xxx";  /* caractere reprezentare arbore, info */

AHeap AlocaHeap(int n, TRel r)
{
    AHeap a = (AHeap)malloc(sizeof(THeap));
    if(!a) return NULL;
    a->v = (int*)malloc(sizeof(int) * n);
    if (!a->v) {free(a); return NULL;}
    a->Max = n; a->ne = 0; a->rel = r;
    return a;
}

void DistrugeHeap(AHeap* aa)
{
    free((*aa)->v);
    free(*aa);
    *aa = NULL;
}

void Afi(AHeap a, int k, int centru, int linie, int dif)
     /*- functie auxiliara - pregateste desen arbore, cu radacina in centru linie
	 dif - distanta pe orizontala intre radacina si cei doi descendenti
	       Exemple:  dif = 5    |     dif = 2    |
				   xxx                 xxx
				___/ \___              / \
     -*/
{ int s, d;
  desen[linie][0] = ':';
  if (dif <= 1)      /* spatiu de afisare insuficient -> ... */
    { memset (desen[linie]+centru, '.', 3); return; }
    
  desen[linie][centru] = '|';      /* legatura spre radacina */
  sprintf (cri, "%3i", a->v[k]);   /* converteste valoare info la 3 caractere */
  d = (cri[0] == ' ') ? 2 : 1;     /* decalaj fata de centru */
  memcpy(desen[linie+1] + centru - d, cri, 3); /* copiaza cele 3 caractere in desen */
  desen[linie+1][0] = ':';  desen[linie+2][0] = ':'; 
  
  if ((s = k * 2 + 1) < a->ne)
  { desen[linie+2][centru-1] = '/';
    memset(desen[linie+2] + centru - dif + 1, '_', dif-2);
    Afi(a, s, centru - dif, linie + 3, (dif+1)/2 );
  }
    
  if (s + 1 < a->ne)
  { desen[linie + 2][centru+1] = '\\';
    memset (desen[linie+2] + centru + 2, '_', dif-2);
    Afi(a, s + 1, centru + dif, linie + 3, (dif+1)/2);
  }
}

void AfiHeap(AHeap a, int linie)
     /*- afiseaza arborele r in partea superioara a ecranului -*/
{ int j;
  for (j = 0; j < 20; j++) memset (desen[j], ' ', 79);
  if (a->ne == 0)
    printf("\t\t\t\t-=- Arbore VID -=-\n");
  else
  { printf("\n");
    Afi(a,0,40,0,19); /* afiseaza incepand de la mijlocul primei linii de pe ecran */
    for (j = 0; j < 16 && desen[j][0] == ':'; j++)
      { desen[j][79] = '\0'; printf("%s\n", desen[j]+1); }
  }
  printf("\n");
}


int MaiMic (int a, int b)
{ return a < b ? -1 : (a < b); }

void InserareHeap(AHeap h, int x)
{
  if (h->ne + 1 == h->Max)
  {
    return;
  }

  int index = h->ne;
  h->v[h->ne++] = x;
  while (h->v[(index-1)/2] > x && index != 0)
  {
    int aux = h->v[(index-1)/2];
    h->v[(index-1)/2] = h->v[index];
    h->v[index] = aux;

    index = (index-1)/2;
  }
}

int ExtragereHeap(AHeap h)
{
  if (h->ne == 0)
    return -1;

  int x = h->v[0];
  h->v[0] = h->v[--h->ne];

  int index = 0;
  int aux;
  while (index != h->ne)
  {
    if (2*index+1 >= h->ne)
      break;
    if (h->v[index] > h->v[2*index+1] &&
        h->v[index] > h->v[2*index+2])
    {
      if (h->v[2*index+1] >= h->v[2*index+2])
      {
        aux = h->v[2*index+2];
        h->v[2*index+2] = h->v[index];
        h->v[index] = aux;

        index = 2*index+2;
      }
      else
      {
        aux = h->v[2*index+1];
        h->v[2*index+1] = h->v[index];
        h->v[index] = aux;

        index = 2*index+1;
      }
      continue;
    }
    if (h->v[index] > h->v[2*index+1])
    {
      aux = h->v[2*index+1];
      h->v[2*index+1] = h->v[index];
      h->v[index] = aux;

      index = 2*index+1;
      continue;
    }
    if (h->v[index] > h->v[2*index+2])
    {
      aux = h->v[2*index+2];
      h->v[2*index+2] = h->v[index];
      h->v[index] = aux;

      index = 2*index+2;
      continue;
    }

    break;
  }

  return x;
}

void HeapSort(AHeap h)
{
  int x;
  while ((x = ExtragereHeap(h)) != -1)
  {
    printf("%d ", x);
  }
  printf("\n");
}

void Bonus(AHeap h)
{
  int index = 0;
  while (index < h->ne)
  {
    if (2*index+1 >= h->ne)
      break;
    if (h->v[index] > h->v[2*index+1] ||
        h->v[index] > h->v[2*index+2])
    {
      printf("NU ESTE!\n");
      return;
    }
    index++;
  }
  printf("ESTE!\n");
}

int main()
{
    AHeap arb;
    int testv[] = {5, 10, 2, 12, 7, 3}, i;
    
    arb = AlocaHeap(NMAX, MaiMic);
    if(!arb) return 0;
    
    /* copiaza in heap cele 6 elemente din vectorul testv */
    for(i = 0; i < 6; i++)
        arb->v[arb->ne++] = testv[i];
    
    AfiHeap(arb, 13);

    printf("Bonus: \n");
    Bonus(arb);
    DistrugeHeap(&arb);
    return 1;
}