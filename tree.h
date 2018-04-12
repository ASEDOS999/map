#ifndef __tree__
	#define __tree__
	#include "map.h"
	#define _branch_methods \
		 _map_enter_methods;\
                struct map_enter* prev;\
                struct map_enter* left;\
                struct map_enter* right;\
                data* value;
	struct branch{
		_branch_methods;
	}typedef branch;
	struct tree{
		_map_methods;
		int (*data_cmp)(data* a, data* b); //<- is it should be plasxed here?
		struct map_enter* root;  //////////<- about enters
	}typedef tree;
	struct map* tree_create( int (*data_cmp)(data* a, data* b));
	struct map_enter* tree_insert(struct map* this_map, data* d);
	void tree_delete(struct map* this_map);
	struct map_enter* tree_search(struct map * this_map, data* d);
	struct map_enter* tree_prev(struct map* this_map, struct map_enter* );
	struct map_enter* tree_next(struct map* this_map, struct map_enter* );
	void tree_remove(struct map* this_map, struct map_enter* );
	struct map_enter* tree_first(struct map* this_map);
	struct map_enter* tree_last(struct map* this_map);
	struct map_enter* tree_end(struct map* this_map);
#endif
// OLD
/*#ifndef __tree__
	#define __tree__
	#include "map.h"
	struct branch{
		_map_enter_methods;
		struct branch* prev;
		struct branch* left;
		struct branch* right;
		data* value;
	}typedef branch;
	struct tree{
		_map_methods;
		int (*data_cmp)(data* a, data* b); //<- is it should be plasxed here?
		struct map_enter* root;  //////////<- about enters
	}typedef tree;
	struct map* tree_create();
	void tree_insert(struct map* this_map, data* d);
	void tree_delete(struct map* this_map, struct map* map_enter);
	struct map* tree_search(struct map* this_map, data* d);
	struct map* tree_next(struct map* this_map, struct map* map_enter);
	struct map* tree_prev(struct map* this_map, struct map* map_enter);
#endif
*/ 
// OLD\


//OLD
/*#ifndef __tree__
	#define __tree__
	#include "map.h"
	struct branch{
		_map_enter_methods;
		struct branch* prev;
		struct branch* left;
		struct branch* right;
		data* value;
	}typedef branch;
	struct tree{
		_map_methods;
		int (*data_cmp)(data* a, data* b); //<- is it should be plasxed here?
		struct map_enter* root;  //////////<- about enters
	}typedef tree;
	struct map* tree_create( int (*data_cmp)(data* a, data* b));
	void tree_insert(struct map* this_map, data* d);
	void tree_delete(struct map* this_map);
	struct branch* tree_search(struct map * this_map, data* d);
	struct branch* tree_prev(struct map* this_map, struct branch* br);
	struct branch* tree_next(struct map* this_map, struct branch* br);
	void tree_remove(struct map* this_map, struct branch* br);
#endif*/
//OLD\

//
