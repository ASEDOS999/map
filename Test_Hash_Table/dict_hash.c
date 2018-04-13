#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include"../tree.h"
#include"../hash.h"

struct record{
	char* lable;
	int number;
}typedef rec;

#define length 80
int main(){
	map* hash_table = hash_create(hashing);
//	printf("Hash table was created.");
	FILE* file = fopen("stdin", "r");

	if (file == NULL)
	{
		perror("Trouble with file");
		return 0;
	}

	int c = fgetc(file);
	char *s;

	while(c != EOF)
	{
		int i = 0;
		while(isalnum(c))
		{
			s = malloc(length);
			s[i] = c;
			i++;
			c = fgetc(file);
		}
		if(i > 0)
		{
			elem* inp;
			if((inp = (elem*)hash_table->search(hash_table, (data*)s)) == NULL)
			{
				inp = malloc(sizeof(elem*));
				inp->value = (data*)malloc(sizeof(int));
				*((int*)inp->value) = 1;
				inp->key = (data*)s;
				hash_table->insert(hash_table, (data*)inp);
				free(inp);
			}
			else
			{
				(*((int*)inp->value))++;
				free(s);
			}
		}
		s = NULL;
	}
	fclose(file);

	map_enter* i;
	for(i = hash_table->first(hash_table); i != hash_table->last(hash_table); i = hash_table->get_next(hash_table, i))
		if(i != NULL)
			printf("%s %d", (char*)(((elem*)i)->key), *(int*)(((elem*)i)->value));
		else
		{
			perror("error of search in out");
			return 0;
		}

	hash_delete(hash_table);
	free(hash_table);
	return 0;
}
