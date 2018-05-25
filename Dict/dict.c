#include "../hash.h"
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

//The most length of words in text:
#define LEN 80

struct element{
	char* str;
	int val;
};

int hashing(data* key)
{
	char* s = ((struct element*)(key))->str;
	int sum = 0, i;
	for(i = 0; i < LEN; i++)
		sum = sum + s[i];
	return sum;
}

int key_equal(data* key1, data* key2)
{
	if((key1 == NULL) || (key2 == NULL))
		return 0;
	char* s1 = ((struct element*)(key1))->str;
	char* s2 = ((struct element*)(key2))->str;
	return !(strcmp(s1, s2));
}



int main()
{
	FILE* f = stdin;
	map* T = hash_create(hashing, key_equal);
	char c, *string;
	int in_word = 0;
	int i = 0;
	for(c = fgetc(f); c != EOF; c = fgetc(f))
	{
		if (isalnum(c))
		{
			if(in_word == 0)
			{
				in_word = 1;
				string = malloc(LEN);
			}
			string[i] = c;
			i++;
		}
		else
			if(in_word == 1)
			{
				in_word = 0;
				string[i] = '\0';
				struct element* inp = malloc(sizeof(struct element));
				inp->str = string;
				inp->val = 1;
				map_enter* u;
				u = T->search(T, (data*)inp);
				if(u != NULL)
				{
					((struct element*)(u->get_val(u)))->val += 1;
				}
				else
					T->insert(T, (data*)inp);
				i = 0;
			}
	}

	map_enter* j;
	for(j = T->first(T); j != T->end(T); j = T->get_next(T, j))
		printf("%s %d\n", ((struct element*)(j->get_val(j)))->str, ((struct element*)(j->get_val(j)))->val);

	return 0;
}
