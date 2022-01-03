#include "THeader.h"

TStudent * AlocStudentInfo (char nume[30], char prenume[30], int notaPC, int notaSD) {
	TStudent * studentInfo = malloc(sizeof(TStudent));
	if (!studentInfo)
		return NULL;

	strcpy(studentInfo->nume, nume);
	strcpy(studentInfo->prenume, prenume);
	studentInfo->notaPC = notaPC;
	studentInfo->notaSD = notaSD;

	return studentInfo;
}


TLista AlocCelula(TStudent * studentInfo) {
	// Alocare spatiu memorie
	TLista aux = (TLista) malloc(sizeof(TCelula));
	if (!aux)
		return NULL;

	// Completare camp info cu datele studentului
	aux->info = malloc(sizeof(TStudent));
	memcpy(aux->info, studentInfo, sizeof(TStudent));

	// Initializare camp urmator cu NULL
	aux->urm = NULL;

	return aux;
}


void inserareSfarsit(ALista aL, TLista aux) {
	TLista L = *aL;
	TLista ant = NULL;

	while (L != NULL) {
		ant = L;
		L = L->urm;
	}

	if (ant == NULL)
		*aL = aux;
	else
		ant->urm = aux;
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

TLista Probl2(ALista aL, int *elem_mut, int *elem_ram)
{
	TLista L_new = NULL;
	TLista L = *aL;
	TLista ant = NULL;
	TLista aux;
	*elem_mut = 0;
	*elem_ram = 0;

	while (L != NULL)
	{
		if (L->info->notaSD >= 5 && L->info->notaPC < 5)
		{
			TLista aux = L;
			if (!aux)
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

			TLista q = L_new;
			TLista q_ant = NULL;

			while(q && q->info->notaSD > aux->info->notaSD)
			{
				q_ant = q;
				q = q->urm;
			}

			if (!q_ant)
			{
				L_new = aux;
				aux->urm = q;
			}
			else
			{
				q_ant->urm = aux;
				aux->urm = q;
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
	return L_new;
}

TLista Bonus(TLista L, int k)
{
	TLista aux = L;

	int nr = 0;
	while (nr < k)
	{
		aux = aux->urm;
		nr++;
	}

	while (aux)
	{
		L = L->urm;
		aux = aux->urm;
	}

	return L;
}

void AfisareStudenti(TLista L) { 
	printf("Studenti: [\n");
	for (; L != NULL; L = L->urm) {
		printf("(NUME: %s, PRENUME: %s, NOTA_PC: %d, NOTA_SD: %d)\n", 
			L->info->nume, L->info->prenume, L->info->notaPC, L->info->notaSD);
	}
	printf("]\n"); 
}


TLista initializareListaStudenti(int n) {
	char nume[30], prenume[30];
	int notaPC, notaSD;

	// Lista cu studenti
	TLista L = NULL;

	// Citire info pentru fiecare student + Construire celula + inserare celula in L
	for (int i = 0; i < n; i++) {
		printf("Nume: ");
		scanf("%s", nume);
		printf("Prenume: ");
		scanf("%s", prenume);
		printf("Nota PC: ");
		scanf("%d", &notaPC);
		printf("Nota SD: ");
		scanf("%d", &notaSD);

		TStudent * studentInfo = AlocStudentInfo(nume, prenume, notaPC, notaSD);

		TLista student = AlocCelula(studentInfo);
		if (!student)
			continue;
		
		inserareOrdonata(&L, student);
	}

	return L;
}