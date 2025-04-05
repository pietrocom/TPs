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

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max) {
	return rand() % (max - min + 1) + min;
}

int modulo(long a) {
	if (a < 0)
		return -a;
	return a;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b) {
	if (b == 0)
		return modulo(a);
	return mdc(b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b) {
	return ((a * b) / mdc(a, b));
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r) {
	if (!valido_r(r)) return r; 

	long divisor = mdc(r.num, r.den);
	r.num /= divisor;
	r.den /= divisor;

        // Ajusta o sinal
	if (r.den < 0) {
        	r.num = -r.num;
        	r.den = -r.den;
	}

	return r;
}

/* implemente as demais funções de racional.h aqui */

struct racional cria_r (long numerador, long denominador) {
	struct racional r;
	r.den = denominador;
	r.num = numerador;
	return r;	
}

int valido_r (struct racional r) {
	if (r.den == 0){
		return 0;
	}
	return 1;
}

struct racional sorteia_r (long min, long max) {
	struct racional r;
	r.num = aleat(min, max);
	r.den = aleat(min, max);
	return simplifica_r(r);
}

void imprime_r (struct racional r) {
    	r = simplifica_r(r);
    	if (!valido_r(r)){                 // Testar se den != 0
        	printf("NaN");
    	} else if (r.num == 0) {           // Se num 0
        	printf("0");
    	} else if (r.den == 1) {           // Se den for 1
        	printf("%ld", r.num);
    	} else if (r.num == r.den) {       // Se den == num
        	printf("1");
    	} else {
        	printf("%ld/%ld", r.num, r.den);   // Caso contrario, imprime normalmente
    	}
}

int compara_r (struct racional r1, struct racional r2) {
	if ((!valido_r(r1)) || (!valido_r(r2))) {
		return -2;                         // Caso r1 ou r2 sejam invalidos
	}
	
	r1 = simplifica_r(r1);
	r2 = simplifica_r(r2);

	long minimo_multiplo_comum = mmc(r1.den, r2.den);
	long aux_1 = r1.num * minimo_multiplo_comum / r1.den;
	long aux_2 = r2.num * minimo_multiplo_comum / r2.den;	
	
	if (aux_1 < aux_2) {
		return -1;                        
	}

	if (aux_1 == aux_2) {
		return 0;                         
	}
	
	return 1;                                 // Caso r1 > r2 
}

int soma_r (struct racional r1, struct racional r2, struct racional *r3) {	
	if ((!valido_r(r1)) || (!valido_r(r2)) || (r3 == NULL))
		return 0;             // Os dois casos em que a funcao deve retornar 0
	
	long minimo_multiplo_comum = mmc(r1.den, r2.den);
	r1.num = r1.num * minimo_multiplo_comum / r1.den;
	r2.num = r2.num * minimo_multiplo_comum / r2.den;
	long numerador_soma = r1.num + r2.num;
	
	(*r3).num = numerador_soma;
	(*r3).den = minimo_multiplo_comum;

	*r3 = simplifica_r(*r3);

	return 1;                     
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3) {
	r2.num = -r2.num;
	return soma_r (r1, r2, r3);
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3) {
	if ((!valido_r(r1)) || (!valido_r(r2)) || (r3 == NULL))
		return 0;         

	(*r3).num = r1.num * r2.num;
	(*r3).den = r1.den * r2.den;
	*r3 = simplifica_r(*r3);

	return 1;                      // Retorna 1 c.c.
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3) {
	if ((!valido_r(r1)) || (!valido_r(r2)) || (r3 == NULL))
		return 0;           

	(*r3).num = r1.num * r2.den;
	(*r3).den = r1.den * r2.num;
	*r3 = simplifica_r(*r3);

	return 1;                      // Retorna 1 c.c.
}
