/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */
void le_vetor (struct racional *vetor, int n) {
	for (int i = 0; i < n; i++) {
		scanf("%ld", &vetor[i].num);
		scanf("%ld", &vetor[i].den);    // Le os numeradores e denominadores dos n racionais
	}
}

void imprime_vetor_original (struct racional *vetor, int n) {
	printf("VETOR = ");
	for (int i = 0; i < n; i++) {
		imprime_r(vetor[i]);
		printf(" ");
	}
	printf("\n");
}


void elimina_invalido (struct racional *vetor, int *n) {
	int i = 0;
	int j = *n - 1;
	while (i <= j) {
   		if (!valido_r(vetor[i])) {
        		// Encontra o último elemento válido no vetor tal que j < i
       			while (j > i && !valido_r(vetor[j])) 
            			j--;                                     	
        		if (j >= i) {
            			vetor[i] = vetor[j];
            			j--;          		
			}
    		}
    		i++; 
	}	
	*n = j + 1;	
}

void imprime_vetor_resultante (struct racional *vetor, int j) {
	printf("VETOR = ");
	for (int i = 0; i < j; i++) {
		imprime_r(vetor[i]);
		printf(" ");
	}
	printf("\n");
}

// Inspirado em algo parecido com o Selection Sort
void ordena_vetor (struct racional *vetor, int tam) {
	for (int i = 0; i < tam - 1; i++) {
		int menor_indice = i;                    
		for (int j = i + 1; j < tam; j++) {
			if (compara_r(vetor[menor_indice], vetor[j]) > 0)
				menor_indice = j;
		}
		if (menor_indice != i) {
			struct racional temp = vetor[i];
			vetor[i] = vetor[menor_indice];
			vetor[menor_indice] = temp;
		}
	}
}

void imprime_vetor_ordenado (struct racional *vetor, int tam) {
	printf("VETOR = ");
	for (int i = 0; i < tam; i++) {
		imprime_r(vetor[i]);
		printf(" ");
	}
	printf("\n");
}

void soma_elementos (struct racional *vetor, struct racional *soma, int tam) {
	(*soma).num = 0;
	(*soma).den = 1;
	for (int i = 0; i < tam; i++) 
		soma_r(*soma, vetor[i], soma);
}

void imprime_soma (struct racional *soma) {
	printf("SOMA = ");
	imprime_r(*soma);	
}


/* programa principal */
int main () {

	struct racional vetor[100];
	int n;
	scanf("%d", &n);

	if ((n <= 0) || (n >= 100)) {
		return -5;                      // Confere se n atende as especificacoes
	}                                       // Se nao, retorna um codigo de erro

	le_vetor (vetor, n);

	imprime_vetor_original(vetor, n);

	elimina_invalido(vetor, &n);   

	imprime_vetor_resultante(vetor, n);

	ordena_vetor(vetor, n);

	imprime_vetor_ordenado(vetor, n);

	struct racional soma;
	soma_elementos(vetor, &soma, n);

	imprime_soma(&soma);

	printf("\n");

	return (0) ;
}
