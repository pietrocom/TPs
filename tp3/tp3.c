/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

void le_racionais (struct racional **v, int n) {
	for (int i = 0; i < n; i++) {
		long num, den;
		scanf("%li%li", &num, &den);
		v[i] = cria_r(num, den); 
	}
}

void imprime_vetor (struct racional **v, int n) {
	printf("VETOR = ");
	int i = 0;
	
	if (i < n) {
		imprime_r(v[i]);
		i++;
	}

	while (i < n) {
		printf(" ");
		imprime_r(v[i]);
		i++;
	}

	printf("\n");
}

int elimina_invalidos (struct racional **v, int n) {
	int i = 0;
	int j = n - 1;
	struct racional *aux;
	// Indo da esquerda para direita
	while (i <= j) {
		if (!valido_r(v[i])) {
			// Indo da direita para a esquerda
			while ((j > i) && !valido_r(v[j])) 
				j--;
			aux = v[i];
			v[i] = v[j];
			v[j] = aux;
		}
		i++;
	}
	if (n == j + 1)
		return j + 1;
	return j;
}

void troca (struct racional **v, int maior_idx, int n) {
	struct racional *aux = v[maior_idx];
	v[maior_idx] = v[n];
	v[n] = aux;
}

// Algoritmo baseado no Selection Sort
void ordena_vetor (struct racional **v, int n) {
	for (int i = 0; i < n - 1; i++) {
		int min_idx = i;
		for (int j = i + 1; j < n; j++) {
			if (compara_r(v[j], v[min_idx]) == -1) {
				min_idx = j;
			}
		}
		if (min_idx != i) {
			struct racional *temp = v[i];
			v[i] = v[min_idx];
			v[min_idx] = temp;
		}
	}	
}

void soma_elementos (struct racional **v, struct racional *soma, int tam) {
	for (int i = 0; i < tam; i++) 
		soma_r(soma, v[i], soma);
}

void libera_vetor(struct racional **v, int n) {
	for (int i = 0; i < n; i++) {
		destroi_r(v[i]);
		v[i] = NULL;
	}
}

/* programa principal */
int main ()
{
	int n;
	scanf("%d", &n);
	if ((n <= 0) || (n >= 100))
		return -5;           // Testa se n atende as exigencias
	
	struct racional **v;
       	v = malloc(sizeof(struct racional *) * n);
	if (!v)
		return -4;

	le_racionais(v, n);
	imprime_vetor(v, n);

	int tam = elimina_invalidos(v, n);
	imprime_vetor(v, tam);

	ordena_vetor(v, tam);
	imprime_vetor(v, tam);

	struct racional *soma = cria_r(0, 1);
	soma_elementos(v, soma, tam);

	printf("SOMA = ");
	imprime_r(soma);
	printf("\n");
	
	libera_vetor(v, n);

	imprime_vetor(v, tam);

	free(v);
	v = NULL;

	destroi_r(soma);

	return (0);
}

