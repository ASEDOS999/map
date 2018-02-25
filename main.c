#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
#include"hash.h"
//#include<conio.h>

int main(){
	int cond = 1;
	int index, i;
	while(1){
		system("clear");
		printf("1 - to work with trees\n2 - to work with hash tables\n3 - exit\n");
		scanf("%d", &cond);
		system("clear");
		if (cond == 1){//work with trees
		}
		if(cond == 2){ //work with hash tables
			map** hash_tables = NULL;
			int num_hash = 0;
			printf("Choose a point:\n");
			printf("1 - to create a new hash table\n2 - to delete an old hash table\n3 - to insert a new pair of a value and a hash\n");
			printf("4 - to search a pair through a key\n5 - to remove a pair with a key\n6 - to return a previous element(key)\n7 - to return the next element(key)\n");
			printf("8 - cancel\n");
			scanf("%d", &cond);
			if(cond == 1){
				i = 0;
				while(hash_tables[i] != NULL && i < num_hash)
					i++;
				if(i == num_hash){
					num_hash++;
					if((hash_tables = (map**)malloc(num_hash * sizeof(map*))) == NULL)
						perror("realloc");
				}
				hash_tables[i] = hash_create(hashing);
			}
			if(cond == 2){
				printf("Input index of old hash table\n");
				scanf("%d", &index);
				hash_delete(hash_tables[index]);
			}
			if(cond == 3){
			}
			if(cond == 4){
			}
			if(cond == 5){
			}
			if(cond == 6){
			}
			if(cond == 7){
			}
		}
		if(cond == 3)
			return 0;
	}
	return 0;
}
