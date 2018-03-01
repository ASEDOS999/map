#include<stdio.h>
#include<stdlib.h>
#include"../hash.h"
#include"../tree.h"

int main(){
	map* hash_tables = NULL;
	if((hash_tables = (map*)malloc(sizeof(map))) == NULL)
		perror("realloc");
	hash_tables = hash_create(hashing);
	hash_delete(hash_tables);
	printf("Created hash table was deleted success\n");
	return 0;
}

