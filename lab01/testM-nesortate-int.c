/*-- testM-nesortate-int.c --*/
#include "multimeV.h"

/*-- functie de afisare multime intregi --*/
void AfisareMultime_int(TMultime *m)
{
	int *x = (int*)(m->p), n = Cardinal(m), i = 0;
	printf("[");
	for( ; i < n; i++)
		if(i != n-1) printf(" %i,", x[i]);
		else printf(" %i ]", x[i]);
	printf("\n");
}

int compI(const void *a, const void *b) /*-- functie de comparare --*/
{
	return *(int*)a - *(int*)b;
}

int Intersectie(TMultime *a, TMultime *b, TMultime *r)
{
	char *pa, *sf = (char*)(a->s);
	for(pa = (char*)(a->p); pa < sf; pa += a->d)
	{
		if(Apartine(pa, b))
		{
			Adauga(pa, r);
		}
	}

	return Cardinal(r);
}

int Diferenta0(TMultime *a, TMultime *b, TMultime *y)
{
	char *pa, *sfa = (char*)(a->s),
		 *pb, *sfb = (char*)(b->s);

	pb = (char*)(b->p);
	for(pa = (char*)(a->p); pa < sfa; pa += a->d)
	{
		while(a->cmp(pa, pb) > 0)
		{
			pb += b->d;
		}

		if (a->cmp(pa, pb))
		{
			Adauga(pa, y);
		}
	}

	return Cardinal(y);
}

int Transforma(TMultime *a, TMultime *b)
{
	char *pa, *sfa = (char*)(a->s),
		 *pb, *sfb = (char*)(b->s);

	pa = (char*)(a->p);
	for(pb = (char*)(b->p); pb < sfb; pb += b->d)
	{
		if (a->cmp(pa, pb))
		{
			Adauga(pb, a);
		}
		else
		{
			pa += a->d;
		}
	}

	return Cardinal(a);
}

int main()
{
	int va[20] = {-9, -4, 2, 3, 4, 5, 6}, nva = 7,
		vb[10] = {-4, 3, 5, 6, 7, 8, 9}, nvb = 7; 
	TMultime *a, *b;
	int i, rez;
	
	/* constructie multime a */
	a = InitD(100, sizeof(int), compI);
	if(!a) {printf("eroare initializare\n"); return 1;}
	printf("\nConstructie multime a, cu elementele: ");
	for(i = 0; i < nva; i++) printf("%i ", va[i]);
		printf("\n");
	for(i = 0; i < nva; i++) 
	{ 
		rez = Adauga((void*)(va+i), a);
		printf("%i %s\n", va[i], rez? "adaugat" : "exista deja");
	}
	printf("Cardinal(a) = %d,  ", Cardinal(a)); 
	printf("a: "); AfisareMultime_int(a);

	
	/* constructie multime b */
	b=InitD(100, sizeof(int), compI); 
	printf("\nConstructie multime b, cu elementele: ");
	for(i = 0; i < nvb; i++) printf("%i ", vb[i]);
	printf("\n");
	for(i = 0; i < nvb; i++) 
	{
		rez = Adauga((void*)(vb+i), b);
		printf("%i %s\n", vb[i], rez? "adaugat" : "exista deja");
	}
	printf("Cardinal(b) = %d, ", Cardinal(b)); 
	printf("b: "); AfisareMultime_int(b);
	
	/* apeluri functii implementate */

	TMultime *r;
	r = InitD(Cardinal(a), sizeof(int), compI);
	printf("\nPROBLEMA 1: %d\n", Intersectie(a, b, r));
	AfisareMultime_int(r);

	TMultime *y;
	y = InitD(Cardinal(a), sizeof(int), compI);
	printf("\nPROBLEMA 2: %d\n", Diferenta0(a, b, y));
	AfisareMultime_int(y);

	printf("\nBONUS: %d\n", Transforma(a, b));
	AfisareMultime_int(a);

	DistrugeM(&a);
	DistrugeM(&b); 
	return 0;
}