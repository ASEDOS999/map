#include<stdio.h>
#include<stdlib.h>
#include"../hash.h"
#include"../tree.h"
#include<time.h>
int main(){
	map** hash_tables = NULL;
	if((hash_tables = (map**)malloc(sizeof(map*))) == NULL)
		perror("realloc");
	hash_tables[0] = hash_create(hashing);

	srand(time(NULL));
	int N = rand() % 20000;
	int i = 0;
	int k;
	data* input = malloc(sizeof(data));
	int* key = malloc(4);;
	int* value = malloc(4);
	elem* new_elem = malloc(sizeof(elem));
	while(i < N){

		(*key) = rand();
		(*value) = rand();
		new_elem->value = (data*)value;
		new_elem->key = (data*)key;
		input->value = (void*)new_elem;
		hash_insert(hash_tables[0], input);
		hash* h = (hash*)hash_tables[0];
		elem** beg = (elem**)h->start;
		k = hashing(new_elem->key);
		if (!(*((int*)(beg[k]->key)) == *key && *((int*)(beg[k]->value)) == *value)){
			printf("Invalid insert");
			exit(0);
		}
		i++;
	}

	hash_delete(hash_tables[0]);
	free(input);
	free(key);
	free(value);
	free(new_elem);
	free(hash_tables);
	printf("Data was inserted success. N = %d\n", N);
	return 0;
}
