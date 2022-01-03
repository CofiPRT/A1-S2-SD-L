/*-- testHash.c  */
#include "tlg.h"
#include "thash.h"
#include <string.h>

//generez un cod  unic in functie de primul caracter din sir
int codHashNume(void*a)
{
	char *p = ((TProdus*)a)->nume;
    return (*p-'a');
}

void AfiElProd(void * ae)
{
  TProdus *p = (TProdus*)ae;
  printf("[%s %s %lf]\n", p->nume, p->codProdus, p->pret);
}

TLG GenerareListaProd(size_t nrProd)
{
	/*citesc in ordine pentru nr pers
		numele - max 10 caractere
		cod produs - max 5 caractere 
        pret - double
	 */
    size_t i;
    int rez;
	TLG r = NULL;
	TProdus *p;
    
    printf("Se vor introduce nume, cod produs, pret pentru %zu produse: \n", nrProd);
	for(i = 0; i < nrProd; i++)
	{
        p = (TProdus*)malloc(sizeof(TProdus));
        if(!p) return r;
        printf("introdu nume, cod produs, pret - produs %zu:",i+1);
        scanf("%s%s%lf", p->nume, p->codProdus, &(p->pret));
        
		rez = InsLG(&r,p);
		if(!rez)
			return r;
	}
	return r;
}

//functii care compara 2 persoane dupa nume respectiv dupa telefon
int cmpProdNume(void *p1, void *p2)
{
	return strcmp( ((TProdus*)p1)->nume, ((TProdus*)p2)->nume );
}

int cmpProdCod(void *p1, void *p2)
{
	return strcmp( ((TProdus*)p1)->codProdus, ((TProdus*)p2)->codProdus );
}

int cmpProdPret(void *p1, void *p2)
{
	return ((TProdus*)p1)->pret > ((TProdus*)p2)->pret;
}


//generare tabela hash pe baza listei de produse - functia hash ia in calcul primele 2 caractere ale numelui (convertite in prealabil la lowercase)
TH* GenerareHash(TLG listaProd)
{
    TH *h = NULL;
	TLG p;
    TProdus *produs;
	int rez;
	
	//calcul dimensiuni maxime pt tabela hash
	size_t M = ('z'-'a');
    
	//initializare tabela hash
	h = (TH*)IniTH(M, codHashNume);
	if(!h) return NULL;

	for(p = listaProd; p != NULL; p = p->urm)
	{
		
        produs = (TProdus*)malloc(sizeof(TProdus));
        if(!produs) return h;
        memcpy(produs, p->info, sizeof(TProdus));
		rez = InsTH(h, produs, cmpProdNume);
        if(!rez) {free(produs); return h;}
	}
	
	return h;
}



int delete(TH *h, TFCmp f)
{
	int i = 0;
	TLG ant = NULL;
	TLG aux = NULL;
	int nr = 0;

	TProdus *prod = malloc(sizeof(TProdus));
	prod->pret = 10;

	for (; i < h->M; i++)
	{
		TLG l = h->v[i];
		ant = NULL;
		while (l)
		{
			if (f(l->info, prod) == 1)
			{
				nr++;
				aux = l;
				if (ant == NULL)
				{
					h->v[i] = aux->urm;
				}
				else
				{
					ant->urm = aux->urm;
				}
			}
			else
			{
				ant = l;
			}

			l = l->urm;
		}
	}

	return nr;
}

void insert(TH *h, void *e)
{
	int id = h->fh(e);
	TLG l = h->v[id];
	TLG aux = malloc(sizeof(TCelulaG));

	aux->info = e;
	aux->urm = NULL;

	if (h->v[id] == NULL)
	{
		h->v[id] = aux;
	}
	else
	{
		aux->urm = h->v[id];
		h->v[id] = aux;
	}
}

void rearrange(TH *h)
{
	int nr = 0;
	int i;
	for (i = 0; i < h->M; i++)
	{
		nr += LungimeLG(&h->v[i]);
	}

	TLG x = NULL;
	if (nr == 2*(h->M))
	{


		for (i = 0; i < h->M; i++)
		{
			TLG l = h->v[i];
			while (l)
			{
				TLG prev = l;
				l = l->urm;
				InsLG(&x, l);
			}
		}
	}
	TH *sec = NULL;
	sec = GenerareHash(x);

	h = sec;
}

int main()
{ 
 	TLG x = NULL;
 	TH *h = NULL;

	x = GenerareListaProd(2);
    if(!x)
    {
        printf("Lista nu a putut fi generata\n");
        return 0;
    }
    
    printf("\n");
  	Afisare(&x, AfiElProd);
	
    h = GenerareHash(x);
    printf("Tabela hash:\n");
	AfiTH(h, AfiElProd);
    
    /* secvente de test */
    TProdus *prod = (TProdus*) malloc(sizeof(TProdus));
	prod->pret = 10;
	strcpy(prod->nume, "mara");
	strcpy(prod->codProdus, "123");

	TProdus *prod2 = (TProdus*) malloc(sizeof(TProdus));
	prod2->pret = 10;
	strcpy(prod2->nume, "para");
	strcpy(prod2->codProdus, "321");

	insert(h, prod);
	insert(h, prod2);

	printf("\n\nAfter insert: \n\n");

	AfiTH(h, AfiElProd);

    rearrange(h);

    int nr = 0;
	int i;
	for (i = 0; i < h->M; i++)
	{
		nr += LungimeLG(&h->v[i]);
	}


    printf("\nAfter rearrange\n%d\n", nr);

    AfiTH(h, AfiElProd);

  	Distruge(&x, free);
	DistrTH(&h, free);
  	return 0;
}
