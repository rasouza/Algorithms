#include <stdio.h>
#include <stdlib.h>

int main() {
	int v = 10;
	int *p, *p2, *p3;
	
	printf("\n");
	
	p = (int*) malloc(sizeof *p);
	
	/* p recebe o valor de v */
	*p = v;
	printf("p recebe o valor de v");
	printf("\nv = %d | p = %d\n", v, *p);
	
	/* p2 recebe o endereco de v */
	p2 = &v;
	printf("p2 recebe o endereco de v");
	printf("\nv = %d | p = %d | p2 = %d\n", v, *p, *p2);
	
	/* Modifica o valor de v */
	v = 11;
	printf("v alterado para 11");
	printf("\nv = %d | p = %d | p2 = %d\n", v, *p, *p2);
	
	/* p3 aponta para p */
	p3 = p;
	printf("p3 aponta para p");
	printf("\nv = %d | p = %d | p2 = %d | p3 = %d\n", v, *p, *p2, *p3);
	
	/* p muda de valor */
	*p = 13;
	printf("valor de p alterado para 13");
	printf("\nv = %d | p = %d | p2 = %d | p3 = %d\n", v, *p, *p2, *p3);
	
	/* p3 muda de valor */
	*p3 = 15;
	printf("valor de p3 alterado para 15");
	printf("\nv = %d | p = %d | p2 = %d | p3 = %d\n", v, *p, *p2, *p3);
	
	/* free em p3 */
	free(p3);
	printf("free em p3 (p tambem some)");
	printf("\nv = %d | p = %d | p2 = %d | p3 = %d\n", v, *p, *p2, *p3);
	
	printf("\n");
	
	return 0;
}
