#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int main()
{
	int *v, n, i;
	
	fprintf(stdout, "Digite o numero de elementos de v[]: ");
	scanf("%d", &n);
	
	v = malloc(n*sizeof(v));
	
	for (i = 0; i < n; i++)
	{
		printf("\nDigite o valor do item %d: ", i);
		scanf("%d", &v[i]);
	}
	
	dump(n, v);
	heapsort(n, v);
	dump(n, v);

	return 0;	
}
