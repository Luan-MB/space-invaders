/* Aluno: Luan Machado Bernardt     |     GRR20190363     |     Turma: c    */

#include "lib_lista_si.h"

void insere_elem (t_elem *elem, t_game *g) {

	g->fim->prev->prox = elem;
	elem->prev = g->fim->prev;
	g->fim->prev = elem;
	elem->prox = g->fim;
}

void destroi_lista (t_game *g) {

	t_elem *p = g->ini;
	t_elem *aux;

	while (p != g->fim) {
		aux = p->prox;
		free(p);
		p = aux;
	}
	free(p);
}
