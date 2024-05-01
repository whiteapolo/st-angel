#ifndef LLL_H
#define LLL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct lll_t{
	struct lll_t *next;
	void *info;
} lll_t;

void lll_init(lll_t **m);
void lll_push(lll_t **m, void *info);
void *lll_pop(lll_t **m);

void lll_insert_after(lll_t *l, void *info);
void *lll_remove_after(lll_t *l);

void lll_clear(lll_t **m, void (*free_info)(void *));
void lll_print(lll_t *l, void(*print_info)(void*));




void lll_init(lll_t **m) 
{
	*m = NULL;	
}

void lll_push(lll_t **m, void *info)
{
	lll_t *n = malloc(sizeof(lll_t));
	n->next = *m;
	n->info = info;
	*m = n;
}

void *lll_pop(lll_t **m)
{
	void *info = (*m)->info;
	lll_t *tmp = *m;
	*m = (*m)->next;
	free(tmp);
	return info;
}

void lll_insert_after(lll_t *l, void *info)
{
	lll_t *n = malloc(sizeof(lll_t));
	n->next = l->next;
	n->info = info;
	l->next = n;
}

void *lll_remove_after(lll_t *l)
{
	lll_t *tmp = l->next;
	void *info = tmp->info;
	l->next = l->next->next;
	free(tmp);
	return info;
}

void lll_clear(lll_t **m, void (*free_info)(void *))
{
	if (free_info == NULL) {
		while ((*m)->next)
			lll_remove_after(*m);
	} else {
		while ((*m)->next)
			free_info(lll_remove_after(*m));
		free_info(lll_pop(m));
	}
}

void lll_insert_end(lll_t *l, void *info)
{
	while (l->next) 
		l = l->next;
	lll_insert_after(l, info);
}

void lll_print(lll_t *l, void(*print_info)(void*))
{
	while (l) {
		print_info(l->info);
		l = l->next;
	}
}

#endif
