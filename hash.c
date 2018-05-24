#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <errno.h>

#define DEBAG
#ifdef DEBAG
	#define MAP_CHECK
	#define ELEM_CHECK
#endif


data* get_value(struct map_enter* el){
	if (el == NULL)
		return NULL;
	return ((elem*)el)->value;
}

void list_delete(struct map* this_map, int a){
	hash* m = (hash*) this_map;
	elem** beg = (elem**)m->start;
	if(beg[a] == NULL)  //the list is empty
		return;
	while(beg[a]->next != NULL){
		elem* nel = (elem*)beg[a]->next;
		free((elem*)beg[a]->next);
		beg[a] = ((elem*)nel->next);
	}
	free(beg[a]);
	return;
}

struct map* hash_create(int (*hashing)(data* key), int (*key_equal)(data* key_1, data* key_2)){
	if ((hashing == NULL)||(key_equal == NULL))
		return NULL;
	map* m;
	if( (m = (map*)malloc(sizeof(hash))) == NULL){
		perror("(hash_create, 41)malloc for m");
		return NULL;
	}
	m->insert = hash_insert;
	m->delet = hash_delete;
	m->search = hash_search;
	m->remove = hash_remove;
	m->get_next = hash_next;
	m->get_prev = hash_prev;
	m->first = hash_first;
	m->last = hash_last;
	m->end = hash_end;
	hash* ha = (hash*) m;
	if((ha->start = (map_enter**)malloc(H * sizeof(elem*))) == NULL)
	{
		perror("(hash_create, 46)malloc for ha->start");
		return NULL;
	}
	int i;
	for (i = 0; i < H; i++)
		ha->start[i] = NULL;
	ha->hashing = hashing;
	ha->equal = key_equal;
	return (struct map*) m;
}

int unique(struct map* this_map, data* key){
	struct map_enter* i;
	if((this_map == NULL)||(key == NULL))
		return 0;
	for(i = this_map->first(this_map); i != this_map->end(this_map); i = this_map->get_next(this_map, i))
		if(((hash*)this_map)->equal(((elem*)i)->value, key))
			return 0;
	return 1;
}

struct map_enter* hash_insert(struct map* this_map, data* ent){
	if((this_map == NULL) || (ent == NULL))
		return NULL;
	int k = ((hash*)this_map)->hashing(ent) % H; //pointer to start of list
	map_enter* next_el = NULL;
	elem** beg = (elem**)((hash*)this_map)->start;
	next_el = (map_enter*)beg[k];
	if(unique(this_map, ent))
	{
		beg[k] = NULL;
		if((beg[k] = (elem*)malloc(sizeof(elem))) == NULL)
			return NULL;
		beg[k]->get_val = get_value;
		beg[k]->next = next_el;
		beg[k]->value = ent;
		return (struct map_enter*)beg[k];
	}
	else
		return NULL;
}

void hash_delete(struct map* this_map){
	int i;
	hash* m = (hash*) this_map;
	if(m == NULL)
		return;
	for (i = 0; i < H; i++)
		list_delete(this_map, i);
	free((elem**)m->start);
	free(m);
	return;
}

struct map_enter* hash_search(struct map* this_map, data* key){
	if((this_map == NULL)||(key == NULL))
		return NULL;
	hash* m = (hash*) this_map;
	elem** beg = (elem**)m->start;
	elem* el = beg[m->hashing(key)];
	while ((!(m->equal(key, el->value))) && (el != NULL))
		el = (elem*)el->next;
	return (struct map_enter*) el;
}

void hash_remove(struct map* this_map, struct map_enter* d){
	elem* d_new = (elem*)d;
	data* key = d_new->value;
	hash* m = (hash*) this_map;
	if ((m == NULL)||(d == NULL)){
		return;
	}
	elem** beg = (elem**)m->start;
	elem* el = beg[m->hashing(key)];
	if (el == NULL){
		printf ("Element with this key doesn't exist");
		return;
	}
	elem* prev = NULL;

	while (!(m->equal(key, el->value)) || el == NULL){
		prev = el;
		el = (elem*)el->next;
	}

	if (el == NULL){
		printf("Element with this key doesn't exist");
		return;
	}
	if (prev == NULL){ //element is start of the list
		elem* nel = (elem*)el->next;
		free(el);
		el = nel;
		return;
	}
	else{
		elem* nel = (elem*)el->next;
		free(el);
		prev->next = (map_enter*)nel;
	}
	return;
}

struct map_enter* hash_prev(struct map* this_map, struct map_enter* d){
	if((this_map == NULL)||(d == NULL))
		return NULL;
	elem* d_new = (elem*)d;
	data* key = d_new->value;
	hash* m = (hash*)this_map;
	int k = m->hashing(key);
	elem** beg = (elem**)m->start;
	if(!(m->equal(beg[k]->value, d_new->value)))
	{
		elem* i = (elem*)beg[k]->next;
		elem* prev = beg[k];
		while(!(m->equal(beg[k]->value, d_new->value)) && i->next != NULL)
			i = (elem*)i->next;
		if(!(m->equal(beg[k]->value, d_new->value)) && i->next == NULL)
			return NULL;
		else
			return (struct map_enter*) prev;
	}

	k = (k + H - 1) % H;
	while(k > -1 && beg[k] == NULL)
		k--;
	if(k > -1)
		return (struct map_enter*)beg[k];
	else
		return NULL;
}

struct map_enter* hash_next(struct map* this_map, struct map_enter* d){
	if((this_map == NULL)||(d == NULL))
		return NULL;
	elem* d_new = (elem*)d;
	if(d_new == NULL)
		return NULL;
	data* key = d_new->value;
	if (d_new->next != NULL)
		return (struct map_enter*)d_new->next;

	hash* m = (hash*)this_map;
	int k = (m->hashing(key) + 1) %H;
	elem** beg = (elem**)m->start;

	while(k < H && beg[k] == NULL)
		k++;
	if(k < H)
		return (struct map_enter*)beg[k];
	else
		return NULL;
}

struct map_enter* hash_first(struct map* this_map){
	if(this_map == NULL)
		return NULL;
	elem** beg = (elem**)((hash*)this_map)->start;
	int k = 0;
	while (k < H && beg[k] == NULL)
		k++;
	if (k == H)
		return NULL; //table is empty
	else
		return (struct map_enter*)beg[k];

}

struct map_enter* hash_last(struct map* this_map){
	if(this_map == NULL)
		return NULL;
	hash* m = (hash*)this_map;
	elem** beg = (elem**)m->start;
	int k = H-1;
	while(k >= 0 && beg[k] == NULL)
		k--;
	if(k < 0)
		return NULL; //table is empty
	elem* i = beg[k];
	while(i->next != NULL) //go to the end of list
		i = (elem*)i->next;
	return (struct map_enter*)i;
}

struct map_enter* hash_end(struct map* this_map){
	return NULL;
}
