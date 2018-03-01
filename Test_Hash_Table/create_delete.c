#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"../tree.h"
#include"../hash.h"

int main(){
	map** hash_tables = NULL;
	srand(time(NULL));
	int N = rand() % 1000;
	if((hash_tables = (map**)malloc(N *sizeof(map*))) == NULL)
		perror("(main) malloc");
	int i;
	for(i = 0; i < N; i++)
		hash_tables[i] = hash_create(hashing);
	for(i = 0; i < N; i++)
		hash_delete(hash_tables[i]);
	printf("Hash tables were created and deleted success. Number of used hash tables: %d\n", N);
	free(hash_tables);
	return 0;
}

