#ifndef __hash__
	#define __hash__
	#include "map.h"
	struct elem
	{
		_map_enter_methods;
		struct map_enter* next; //the next element of the list.
		data* value;
		data* key;
	}typedef elem;

	struct hash
	{
		_map_methods;
		int (*hashing)(data* a); //hash function
		struct map_enter** start; //pointer to the pointer to the element with hash function equaling 0
	}typedef hash;


	int hashing (data* key);
	void list_delete(struct map* this_map, int a);

	struct map* hash_create( int (*hashing)(data* key));
	struct map_enter* hash_insert(struct map* this_map, data* ent);
	void hash_delete(struct map* this_map);
	struct map_enter* hash_search(struct map * this_map, data* key);
	void hash_remove(struct map* this_map, struct map_enter* d);
	struct map_enter* hash_prev(struct map* this_map, struct map_enter* d);
	struct map_enter* hash_next(struct map* this_map, struct map_enter* d);

	struct map_enter* hash_first(struct map* this_map);
	struct map_enter* hash_last(struct map* this_map);

#endif
