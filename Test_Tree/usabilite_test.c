#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tree.h"

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
	return (strcmp(ra->lable, rb->lable));
}

int main(int ac, char** av){
	int i;
	rec* tmp;
	map_enter* me;
	map* dict = tree_create(rec_cmp);
	for(i = 1; i < ac; ++i){
		tmp = malloc(sizeof(rec));
		tmp->lable = av[i];
		tmp->number = 1;
		me = dict->insert(dict, (data*)tmp);
		if(((branch *)me)->value != (data*)tmp)
			free(tmp);
	}
	for(me = dict->first(dict); 
		me != dict->end(dict); 
		me = dict->get_next(dict, me))
		{
		printf("%s %d times\n", 
			((rec*)(((branch *)me)->value))->lable, 
			((rec*)(((branch *)me)->value))->number
			);
		
	}
	return 0;
}

