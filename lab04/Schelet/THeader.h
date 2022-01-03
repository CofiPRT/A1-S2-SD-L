#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char nume[30];
	char prenume[30];
	int notaPC;
	int notaSD;
} TStudent;

typedef struct celula {
	TStudent * info;
	struct celula * urm;
} TCelula, *TLista, **ALista;


TStudent * AlocStudentInfo (char nume[30], char prenume[30], int notaPC, int notaSD);
TLista AlocCelula(TStudent * studentInfo);
void inserareSfarsit(ALista aL, TLista aux);
void AfisareStudenti(TLista L);
TLista initializareListaStudenti(int n);

TLista Probl2(ALista aL, int *elem_mut, int *elem_ram);