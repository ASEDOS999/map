#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash.h"
#include<errno.h>

#define DEBAG
#ifdef DEBAG
	#define MAP_CHECK
	#define ELEM_CHECK
#endif

#define H 3089
//it is parametеr of hash function

int hashing(data* key){		//it is hash function
	int* k = (int*)key;
	return ((*k)%H);
}

void list_delete(struct map* this_map, int a){
	hash* m = (hash*) this_map;
	elem* el = ((elem*)m->start + a * (sizeof(elem)));
	while (el->next != NULL){
		elem* nel = (elem*)el->next;
		free(el);
		el = nel;
	}
	free(el);
	return;
}

struct map* hash_create(int (*hashing)(data* key)){
	map* m = malloc(sizeof(hash));
	m->insert = hash_insert;
	m->delet = hash_delete;
	m->search = hash_search;
	m->remove = hash_remove;
	m->get_next = hash_next;
	m->get_prev = hash_prev;
	hash* ha = (hash*) m;
	ha->start = (map_enter**)malloc(H * sizeof(elem*));
	ha->hashing = hashing;
	return (struct map*) m;
}

void hash_insert(struct map* this_map, data* ent){
	elem* ent_new = (elem*)ent->value;
	hash* m = (hash*) this_map;
	elem* el = *((elem**)m->start+hashing(ent_new->key) * sizeof(elem*));
	while (el->next != NULL)
		el = (elem*)el->next;
	if ((el->next = (map_enter*)malloc(sizeof(elem))) == NULL)
		perror("(hash_insert)Return value of malloc equals NULL");
	el = (elem*)el->next;
	el->next = NULL;
	el->value = ent_new->value;
	el->key = ent_new->key;
	return;
}

void hash_delete(struct map* this_map){
	int i;
	for (i = 0; i < H; i++)
		list_delete(this_map, i);
	hash* m = (hash*) this_map;
	free(m->start);
	free(m);
	return;
}

struct map_enter* hash_search(struct map* this_map, data* key){
	hash* m = (hash*) this_map;
	elem* el = *((elem**)m->start + hashing(key) * sizeof(elem*));
	while (el->key != key)
		el = (elem*)el->next;
	return (struct map_enter*) el;
}

void hash_remove(struct map* this_map, struct map_enter* d){
	elem* d_new = (elem*)d;
	data* key = d_new->key;
	hash* m = (hash*) this_map;
	if (m == NULL){
		printf("This map doesn't exist");
		return;
	}
	elem* el = *((elem**)m->start + hashing(key) * sizeof(elem*));
	if (el == NULL){
		printf ("Element with this key doesn't exist");
		return;
	}
	elem* prev = NULL;

	while (el->key != key || el == NULL){
		elem* prev = el;
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
	elem* d_new = (elem*)d;
	data* key = d_new->key;
	int k = hashing(key);
	hash* m = (hash*)this_map;
	elem** arr = (elem**)m->start;
	elem* el = arr[k];
	if (el == NULL){
		printf("Element with this key doesn't exist");
		return NULL;
	}
	elem* prev = NULL;
	while(el->key != key && el->next != NULL){
		prev = el;
		el = (elem*)el->next;
	}
	if(el->key != key && el->next == NULL){
		printf ("Element with this key doesn't exist");
		return NULL;
	}
	if (prev == NULL){
		k = (k + H - 1) % H;
		while((arr[k]) == NULL)
			k = (k + H - 1) % H;
		return (struct map_enter*)arr[k];
	}
	else
		return (struct map_enter*)prev;

}

struct map_enter* hash_next(struct map* this_map, struct map_enter* d){
	elem* d_new = (elem*)d;
	data* key = d_new->key;
	elem* el = (elem*)hash_search(this_map, key);
	if(el->next == NULL){
		int k = (hashing(key)+1) % H;
		hash* m = (hash*)this_map;
		elem** arr = (elem**)m->start;
		while((arr[k]) == NULL)
			k=(k + 1) % H;
		return (struct map_enter*)arr[k];
	}
	else
		return el->next;
}

