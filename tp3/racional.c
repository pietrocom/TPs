/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

int modulo(long a) {
	if (a < 0)
		return -a;
	return a;
}

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b) {
	if (b == 0)
		return modulo(a);
	return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b) {
	return ((a * b) / mdc(a, b));
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r(struct racional *r) {
	if (!valido_r(r))
		return 0;

	long divisor = mdc(r->num, r->den);
	r->num /= divisor;
	r->den /= divisor;

	/* Ajusta o sinal do denominador */
	if (r->den < 0) {
		r->num = -r->num;
		r->den = -r->den;
	}

	return 1;
}

/* implemente as demais funções de racional.h aqui */

struct racional *cria_r(long numerador, long denominador) {
	struct racional *r;
	r = (struct racional*) malloc(sizeof(struct racional));
	if (r == NULL)
		return NULL;

	r->num = numerador;
	r->den = denominador;

	return r;
}

void destroi_r(struct racional *r) {
	free(r);
}

int valido_r(struct racional *r) {
	return ((r != NULL) && (r->den != 0));
}

void imprime_r(struct racional *r) {
	if (r == NULL) {
		printf("NULL");
		return;
	}

	if (!valido_r(r)) {
		printf("NaN");
		return;
	}

	simplifica_r(r);

	if (r->num == 0) {
		printf("0");
	} else if (r->den == 1) {
		printf("%ld", r->num);
	} else if (r->num == r->den) {
		printf("1");
	} else {
		printf("%ld/%ld", r->num, r->den);
	}
}

int compara_r(struct racional *r1, struct racional *r2) {
	if (!valido_r(r1) || !valido_r(r2))
		return -2;

	long minimo = mmc(r1->den, r2->den);
	long num1 = (minimo / r1->den) * r1->num;  // Ajustando os numeradores em função do mmc
	long num2 = (minimo / r2->den) * r2->num;  

	if (num1 < num2)
		return -1;
	if (num1 == num2)
		return 0;
	return 1;
}

int soma_r(struct racional *r1, struct racional *r2, struct racional *r3) {
	if (!valido_r(r1) || !valido_r(r2))
		return 0;

	long minimo = mmc(r1->den, r2->den);
	r3->num = (minimo / r1->den) * r1->num + (minimo / r2->den) * r2->num;
	r3->den = minimo;

	return simplifica_r(r3);
}

int subtrai_r(struct racional *r1, struct racional *r2, struct racional *r3) {
	if (!valido_r(r1) || !valido_r(r2))
		return 0;

	long minimo = mmc(r1->den, r2->den);
	r3->num = (minimo / r1->den) * r1->num - (minimo / r2->den) * r2->num;
	r3->den = minimo;

	return simplifica_r(r3);
}

int multiplica_r(struct racional *r1, struct racional *r2, struct racional *r3) {
	if (!valido_r(r1) || !valido_r(r2))
		return 0;

	r3->num = r1->num * r2->num;
	r3->den = r1->den * r2->den;

	return simplifica_r(r3);
}

int divide_r(struct racional *r1, struct racional *r2, struct racional *r3) {
	if (!valido_r(r1) || !valido_r(r2) || r2->num == 0)
		return 0;

	r3->num = r1->num * r2->den;
	r3->den = r1->den * r2->num;

	return simplifica_r(r3);
}

