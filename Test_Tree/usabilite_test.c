#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include <string.h>
#include <ctype.h>
#define wordsize 80
struct record{
	char* lable;
	int number;
} typedef rec;

int rec_cmp(data* a, data* b){
	rec* ra = (rec *)a;
	rec* rb = (rec *)b;
	if(strcmp(ra->lable, rb->lable) == 0){
		ra->number = ra->number + 1;
	}
	return( -1) * (strcmp(ra->lable, rb->lable));
}
#define dFIN "stdin.txt"
int main(int ac, char** av){
	char* FIN;
	if(ac == 1)
		FIN = dFIN;
	else 
		FIN = av[1];
	FILE *fr = fopen( FIN, "r");
//	FILE *fw = fopen("stdout.txt", "w");
	if (fr == NULL)
	{
			printf("Eror: input file \"%s\"is not found\n", FIN);
		return 0;
	}
//	printf("Ok\n");
	int i, j;
	int c;
	rec* tmp;
	map_enter* me;
	map* dict = tree_create(rec_cmp);
	for(c = fgetc(fr); c != EOF; ){
		while((!isalnum(c)) && (c != EOF))
			c = fgetc(fr);
		tmp = malloc(sizeof(rec));
		tmp->lable = malloc(wordsize);
		j = 0;
//		printf("\n_");
		for(; c != EOF; c = fgetc(fr)){
			/*printf("\\%c/", c);*/
			if(isalnum(c))
			{
				tmp->lable[j] = c;
			}
			else{
				//c = fgetc(fr);
				break;
			}
		j++;
		}
		tmp->lable[j] = 0;
		if(j == 0){
			free(tmp->lable);
			free(tmp);
			//printf("NUL`\n");
			continue;
		}
		
		//printf("_\n");
		//printf("_%s_\n", tmp->lable);
		tmp->number = 1;
		me = dict->insert(dict, (data*)tmp);
	}
	for(me = dict->first(dict); 
		me != dict->end(dict); 
		me = dict->get_next(dict, me))
	{
		printf("\"%s\" %d times\n", 
			((rec*)(me->get_val(me)))->lable, 
			((rec*)(me->get_val(me)))->number
			);
	}
	dict->delet(dict);	
	return 0;
}

