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

#define H 3089 //it is parametеr of hash function

int hashing(data* key){		//it is hash function
	int* k = (int*)key;
	if(key == NULL)
		return 0;
	return ((*k)%H);
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

struct map* hash_create(int (*hashing)(data* key)){
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
	hash* ha = (hash*) m;
	if((ha->start = (map_enter**)malloc(H * sizeof(elem*))) == NULL)
	{
		perror("(hash_create, 46)malloc for ha->start");
		return NULL;
	}
	ha->hashing = hashing;
	return (struct map*) m;
}

void hash_insert(struct map* this_map, data* ent){
	elem* ent_new = (elem*)ent->value;
	hash* m = (hash*) this_map;
	elem** beg = (elem**)m->start;
	int k = hashing(ent_new->key); //pointer to start of list
	map_enter* next_el;
	if(beg[k] != NULL)//list is not empty
		next_el = beg[k]->next;
	else
		next_el = NULL;
	if((beg[k] = (elem*)malloc(sizeof(elem))) == NULL)
		perror("(hash_insert) malloc for el");
	beg[k]->next = next_el;
	beg[k]->value = ent_new->value;
	beg[k]->key = ent_new->key;
	return;
}

void hash_delete(struct map* this_map){
	int i;
	hash* m = (hash*) this_map;
	for (i = 0; i < H; i++)
		list_delete(this_map, i);
	free((elem**)m->start);
	free(m);
	return;
}

struct map_enter* hash_search(struct map* this_map, data* key){
	hash* m = (hash*) this_map;
	elem** beg = (elem**)m->start;
	elem* el = beg[hashing(key)];
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
	elem** beg = (elem**)m->start;
	elem* el = beg[hashing(key)];
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
	elem** beg = (elem**)m->start;
	k = (k + H - 1) % H;
	while(beg[k] == NULL)
		k = (k + H - 1) % H;
	return (struct map_enter*)beg[k];
}

struct map_enter* hash_next(struct map* this_map, struct map_enter* d){
	elem* d_new = (elem*)d;
	data* key = d_new->key;
	int k = (hashing(key)+1) % H;
	hash* m = (hash*)this_map;
	elem** beg = (elem**)m->start;
	k = (k + 1) % H;
	while(beg[k] == NULL)
		k=(k + 1) % H;
	return (struct map_enter*)beg[k];
}

