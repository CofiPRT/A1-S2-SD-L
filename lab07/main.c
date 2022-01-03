#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"

/* numar maxim elemente coada / stiva */
#define MAX 256 

typedef struct
{ 
	int x, y;
} TPct;

int GenereazaCoadaPct(void* c, size_t N, int v1, int v2)
{ 
  	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!IntrQ(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

int GenereazaStivaPct(void* c, size_t N, int v1, int v2)
{ 
	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!Push(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

/* afiseaza coada */
void AfiQ(char antet[], TF1 AfiElem, void *a)
{ 
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf ("%s", antet);          	/* afiseaza antetul */
  	if (VidaQ (a))
      printf ("Coada vida!");
  	else
      PrelQ (a, AfiElem);       	/* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

/* afiseaza stiva */
void AfiS(char antet[], TF1 AfiElem, void *a) 
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */ 
	printf ("%s", antet);          /* afiseaza antetul */
	if (VidaS (a))
    	printf ("Stiva vida!");
  	else
      	Prel_B_V (a, AfiElem);       /* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

int AfiPct(void *a)
{ 
	printf("[%d %d] ", (*(TPct*)a).x, (*(TPct*)a).y); 
	return 1;
}

int isXeven(void *a)
{
  return (*(TPct*)a).x % 2 == 0;
}

int isYodd(void *a)
{
  return (*(TPct*)a).y % 2 != 0;
}

void *probl3(void *a, int nr)
{
  void *c = InitQ(sizeof(TPct), MAX);

  while (!VidaQ(a))
  {
    TPct point;
    ExtrQ(a, &point);

    if (point.x >= nr)
    {
      IntrQ(c, &point);
    }
  }
      
  return c;
}

void *probl4(void *a, int nr)
{
  void *s = InitS(sizeof(TPct), MAX);

  while (!VidaS(a))
  {
    TPct point;
    Pop(a, &point);

    if (point.y <= nr)
    {
      Push(s, &point);
    }
  }
      
  return s;
}

void bonus1(void *a, void *c1, void *c2)
{
  void *aux = InitQ(sizeof(TPct), MAX);

  int index = 1;

  while (!VidaQ(a))
  {
    TPct point;
    ExtrQ(a, &point);

    IntrQ(aux, &point);

    if (index % 2)
    {
      IntrQ(c1, &point);
    }
    else
    {
      IntrQ(c2, &point);
    }

    index++;
  }

  while (!VidaQ(aux))
  {
    TPct point;
    ExtrQ(aux, &point);

    IntrQ(a, &point);
  }
}

void bonus2(void *a, void *s1, void *s2)
{
  void *aux = InitS(sizeof(TPct), MAX);

  int index = 1;

  while (!VidaS(a))
  {
    TPct point;
    Pop(a, &point);

    Push(aux, &point);
  }

  while (!VidaS(aux))
  {
    TPct point;
    Pop(aux, &point);

    Push(a, &point);

    if (index % 2)
    {
      Push(s1, &point);
    }
    else
    {
      Push(s2, &point);
    }

    index++;
  }
}

int main()
{ 
	void *c, *s;
  	int lgc, lgs;

  	c = InitQ(sizeof(TPct),MAX);
	if (!c) 
		return 1;

  	s = InitS(sizeof(TPct),MAX);
	if (!s) 
	{
		DistrQ(&c); 
		return 1;
	}

  	lgc = GenereazaCoadaPct(c, 8, -5, 5);
  	lgs = GenereazaStivaPct(s, 6, 8, 14);
  
	printf("\nCoada cu %d elemente\n", lgc);
  	AfiQ("Elemente coada:\n", AfiPct, c);
  	printf("\n\nStiva cu %d elemente\n", lgs);
   	AfiS("Elemente stiva (baza -> varf):\n", AfiPct, s);

 	/* apeluri functii */
    void *s1 = InitS(sizeof(TPct), MAX);
    void *s2 = InitS(sizeof(TPct), MAX);

    bonus2(s, s1, s2);
    AfiS("Stiva initiala:\n", AfiPct, s);
    AfiS("Stiva impare:\n", AfiPct, s1);
    AfiS("Stiva pare:\n", AfiPct, s2);


	DistrS(&s);
  	DistrQ(&c);
  	return 0;
}