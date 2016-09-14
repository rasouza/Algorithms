#include <stdio.h>
#include <stdlib.h>

void dump(int n, int v[])
{
	int i;
	
	printf("\n[DUMP] Vetor: ");
	for (i = 0; i < n; i++)
	{
		printf("[%d] ", v[i]);
	}
	printf("\n");
}

/* ---------------------------------------
   | Metodo da insercao                  |
   --------------------------------------- */

void insertionSort(int n, int v[])
{
	int i, j, x;
	for (j = 1; j < n; ++j)
	{
		x = v[j];
		
		for (i = j-1; i >= 0 && v[i] > x; --i)
			v[i+1] = v[i];		
		v[i+1] = x;	
	}
	printf("\nOrdenando o vetor v[]\n");
}

/* ---------------------------------------
   | Metodo da selecao                  |
   --------------------------------------- */

void selectionSort(int n, int v[])
{
	int i, j, min, x;
	for (i = 0; i < n-1; i++)
	{
		min = i;
		for (j = i+1; j < n; j++)
			if (v[j] < v[min])
				min = j;
		x = v[i];		
		v[i] = v[min];
		v[min] = x;
	}
	
	printf("\nOrdenando o vetor v[]\n");
}

/* =======================================
   | MergeSort                           |
   ======================================= */

void intercala(int p, int q, int r, int v[])
{
	int i, j, k, *w;
	w = malloc((r-p)*sizeof(int));
	
	i = p;
	j = q;
	k = 0;
	
	while (i < q && j < r)
	{
		if (v[i] <= v[j]) w[k++] = v[i++];
		else w[k++] = v[j++];
	}
	
	while (i < q) w[k++] = v[i++];
	while (j < r) w[k++] = v[j++];
	
	for(i = p; i < r; i++) v[i] = w[i-p];
}

void mergesort(int p, int r, int v[])
{
	if (p < r-1)
	{
		int q = (p + r)/2;
		mergesort(p, q, v);
		mergesort(q, r, v);
		intercala(p, q, r, v);
	}
}

/* =======================================
   | Heapsort                            |
   ======================================= */
   
void peneira(int p, int n, int v[])
{
	int f = 2*p, x = v[p];
	
	while (f <= n)
	{
		/* Pega o no-filho mais valioso */
		
		if (f < n && v[f] < v[f+1]) f++;
		
		/* Se o filho for menor, esta tudo certo */
		if (v[f] <= x)
			break;
		
		v[p] = v[f];
		p = f;
		f = 2*p;	
	}
	v[p] = x;
}

void heapsort(int n, int v[])
{
	int p, m, x;
	for (p = n/2; p > 0; p--)
		peneira(p, n, v);
		
	for(m = n; m >= 2; m--)
	{
		x = v[1];
		v[1] = v[m];
		v[m] = x;
		
		peneira(1, m-1, v);
	}
}
