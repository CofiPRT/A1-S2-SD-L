/*-- heap.h --*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HEAP
#define HEAP

typedef int (*TRel)(int, int); /* relatie intre 2 informatii */
typedef struct
{ int Max, ne;      /* numar maxim de elemente posibil, respectiv numar efectiv de elemente din heap */
  int * v;          /* adresa vectorului (alocat dinamic) prin care este reprezentat heapul */
  TRel rel;         /* functie de comparatie a doua elemente de tip int - folosita pentru implementarea max/min heap */
} THeap, * AHeap;


AHeap AlocaHeap (int, TRel);
void DistrugeHeap (AHeap*);

void AfisareHeap (AHeap, int);

#endif
