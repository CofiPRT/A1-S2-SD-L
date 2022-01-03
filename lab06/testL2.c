#include "lista2.h"

void AfiInt(void * ax)
{
	printf("%d ", *(int*)ax);
}

void CitireLDI(TLDI s, int* lg)
{
	int *ax, x;
 	char ch;

  	printf("se citesc valori numerice, terminate cu caracter nenumeric\n");
	for(*lg = 0; scanf("%i", &x) == 1; )
  	{
        ax = (int*)malloc(sizeof(int));
		if(!ax) return;
	 	*ax = x;
		InsDupa(s->ant, ax);
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');
}

int main()
{
	TLDI s;
	int lg;

	for(; ; )
	{
		s = InitLDI();
		CitireLDI(s, &lg);
		AfisareLDI(s, AfiInt);

		/* apeluri functii */
		Bonus(s, 3);
		AfisareLDI(s, AfiInt);

		DistrLDI(&s);

		printf ("\n  Inca un test ? [d/n]");
		if (getchar() == 'n') break;
	}
    return 1;
}