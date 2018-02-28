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
	elem* el = *((elem**)m->start + a * (sizeof(elem*)));
	if(el == NULL)  //the list is empty
		return;
	while(el->next != NULL)
		free((elem*)el->next);
	free(el);
	return;
}

struct map* hash_create(int (*hashing)(data* key)){
	map* m;
	if( (m = (map*)malloc(sizeof(hash))) == NULL)
	{
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
	elem* el = *((elem**)m->start+hashing(ent_new->key) * sizeof(elem*)); //pointer to start of list
	map_enter* next_el;
	if(el != NULL)//list is not empty
		next_el = el->next;
	else
		next_el = NULL;
	if((el = (elem*)malloc(sizeof(elem*))) == NULL)
		perror("(hash_insert) malloc for el");
	el->next = next_el;
	el->value = ent_new->value;
	el->key = ent_new->key;
	return;
}

void hash_delete(struct map* this_map){
	int i;
	for (i = 0; i < H; i++)
		list_delete(this_map, i);
	hash* m = (hash*) this_map;
	free((elem*)m->start);
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
	while(el->key != key && el->next != NULL)
		el = (elem*)el->next;
	if(el->key != key && el->next == NULL){
		printf ("Element with this key doesn't exist");
		return NULL;
	}
	k = (k + H - 1) % H;
	while((arr[k]) == NULL)
		k = (k + H - 1) % H;
	return (struct map_enter*)arr[k];

}

struct map_enter* hash_next(struct map* this_map, struct map_enter* d){
	elem* d_new = (elem*)d;
	data* key = d_new->key;
	elem* el = (elem*)hash_search(this_map, key);
	int k = (hashing(key)+1) % H;
	hash* m = (hash*)this_map;
	elem** arr = (elem**)m->start;
	while((arr[k]) == NULL)
		k=(k + 1) % H;
	return (struct map_enter*)arr[k];
}

