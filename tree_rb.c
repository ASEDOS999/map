#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define DEBAG
#ifdef DEBAG
        #define MAP_CHECK
        #define BRANCH_CHECK
#endif

struct map_enter* branch_rb_create(struct map_enter* prev, struct map_enter* left, struct map_enter* right, data * d){
        struct map_enter* me = malloc(sizeof(struct branch_rb));
        struct branch_rb* br = (struct branch*)me;
        br->value = d;
        br->prev = prev;
        br->left = left;
        br->right = right;
	br->colour = 1;
        return me;
}
struct map* tree_rb_create( int (*data_cmp)(data* a, data* b)){
	struct map* m = tree_create(data_cmp);
	struct tree* tr = (tree)m;
	tr->insert = tree_rb_insert;
	tr->delete = tree_rb_delete;
	return m;
}
void redparent_reduncle(branch_rb* p, branch_rb* u){
	p->colour = 0;
	u->colour = 0;
	branch_rb* d = (branch_rb*)(p->prev);
	d->colour = 1;
	branch_rb_rebalance(d);
}
void tree_rb_insert(struct map* this_map, data* d){
	br = branch_rb_create(NULL, NULL, NULL, d);
	tree_insert// tyt nado libo peredelyvat` libo kopirob=vat` staryq kod
	if(br->prev == NULL){
		br->colour = 0;
		return;
	}
	branch_rb* p = (branch_rb*)br->prev;
	if(p->colour == 0)
		return;
	branch_rb* g = (branch_rb*)p->prev;
	branch_rb* u = g->right == p ? (branch_rb*)p->left : (branch_rb*)p->right;
	if(u->colour == 1){
		p->colour = 0;
	        u->colour = 0;
        	g->colour = 1;
        	branch_rb_rebalance(g);
		return;
	}
	////////left->left || right->right
	//int le = &(br->left) - br;
	//int le = &(br->right) - br;
	int dir = g->left == p ? &(br->left) - br : &(br->right) - br;
	if(br->left = );
	//
	if(p->right == br){

		g->left = br;
		br->prev = g;
		p->right = br->left;
		((branch_rb*)(br->left))->prev = p;
		br->left = p;
		p->prev = br;
		br = p;
		p = (branch_rb*)br->prev;
	}

	branch_rb** gdir;
	if(g->prev == NULL){
		gdir = &(tree->root);
	}
	else
		((branch_rb*)g->prev)->left == g ? gdir = &(((branch_rb*)g->prev)->left) : &(((branch_rb*)g->prev)->right);	
	*gdir = p;
//	p->prev = g->prev;
	/////tol`ko 1 slychai
	branch_rb** direct;
	branch_rb** ndirect;
	if(p->right == br){
		direct = &(branch_rb*)(p->right);
		ndirect = &(branch_rb*)(p->left);
	}
	else{
		direct = &(branch_rb*)(p->left);
		ndirect = &(branch_rb*)(p->right);
	}
}





