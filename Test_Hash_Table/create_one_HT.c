#include<stdio.h>
#include<stdlib.h>
#include"../tree.h"
#include"../hash.h"

int main(){
	map* hash_tables = NULL;
	if((hash_tables = (map*)malloc(sizeof(map))) == NULL)
		perror("realloc");

	hash_tables = hash_create(hashing);
	printf("Hash table was created success\n");
	return 0;
}

