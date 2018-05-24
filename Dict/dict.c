#include "../hash.h"
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

//The most length of words in text:
#define LEN 80

int hashing(data* key)
{
	return 0;
}

int key_equal(data* key1, data* key2)
{
	return 0;
}

int main(int ac, char** name)
{
	FILE* f;
	if (ac == 2)
		f = fopen(name[1], "r");
	else
		f = fopen("input.txt", "r");

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
				T->insert(T, (data*)string);
				i = 0;
			}
	}

	map_enter* j;
	for(j = T->first(T); j != T->end(T); j = T->get_next(T, j))
		printf("%s\n", (char*)(j->get_val(j)));

	return 0;
}
