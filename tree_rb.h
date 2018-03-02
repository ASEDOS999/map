#ifndef __tree_rb__
        #define __tree_rb__
        #include "tree.h"
        struct branch_rb{
		_branch_methods;
		char colour;
        }typedef branch_rb;
        struct map* tree_rb_create( int (*data_cmp)(data* a, data* b));
        void tree_rb_insert(struct map* this_map, data* d);
	void tree_rb_remove(struct map* this_map, struct map_enter* );
#endif

