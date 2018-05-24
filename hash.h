#ifndef __hash__
	#define __hash__
	#include "map.h"

	#define H 3091

	struct elem
	{
		_map_enter_methods;//get_val(struct map_enter* a);
		struct map_enter* next; //the next element of the list.
		data* value; //it's pair of a key and a value
//		data* key;
	}typedef elem;

	data* get_value(struct map_enter* el);

	struct hash
	{
		_map_methods;
		int (*hashing)(data* a); //hash function
		int (*equal)(data* key_1, data* key_2);
		struct map_enter** start; //pointer to the pointer to the element with hash function equaling 0
	}typedef hash;



	struct map* hash_create(int (*hashing)(data* key), int (*key_equal)(data* key_1, data* key_2));

	void list_delete(struct map* this_map, int a);
	struct map_enter* hash_insert(struct map* this_map, data* ent);
	void hash_delete(struct map* this_map);
	struct map_enter* hash_search(struct map * this_map, data* key);
	void hash_remove(struct map* this_map, struct map_enter* d);
	struct map_enter* hash_prev(struct map* this_map, struct map_enter* d);
	struct map_enter* hash_next(struct map* this_map, struct map_enter* d);

	int unique(struct map* this_map, data* key);

	struct map_enter* hash_first(struct map* this_map);
	struct map_enter* hash_last(struct map* this_map);
	struct map_enter* hash_end(struct map* this_map);
#endif
