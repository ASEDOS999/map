#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define DEBAG
#ifdef DEBAG
	#define MAP_CHECK
	#define BRANCH_CHECK
#endif

/// chto naschet togo chtoby vstavliat` ne tol`ko data no i branch
/*struct branch* branch_create(struct branch* prev, struct branch* left, struct branch* right, data * d){
	struct branch* br = malloc(sizeof(struct branch));
	br->value = d;
	br->prev = prev;
	br->left = left;
	br->right = right;
}*/   // about enter
data* branch_get_value(map_enter* me){
	return ((branch*)me)->value;
}
struct map_enter* branch_create(struct map_enter* prev, struct map_enter* left, struct map_enter* right, data * d){
	struct map_enter* me = malloc(sizeof(struct branch));
	me->get_val = branch_get_value;
	struct branch* br = (struct branch*)me;
	br->value = d;
	br->prev = prev;
	br->left = left;
	br->right = right;
	return me;
}

struct map* tree_create( int (*data_cmp)(data* a, data* b)){
		struct map* m = malloc(sizeof(struct tree));
		m->insert = tree_insert;
		m->delet = tree_delete;
		m->search = tree_search;
		m->get_next = tree_next;
		m->get_prev = tree_prev;
		m->remove = tree_remove;
		struct tree* tr = (struct tree *)m;
		tr->root = NULL;
		tr->data_cmp = data_cmp;
		tr->end = tree_end;
		tr->first = tree_first;
		tr->last = tree_last;
		return m;
}

///////������� ����������!!!!
/*map_enter* branch_insert(map_enter* sub, map_enter* obj, int (*data_cmp)(data* a, data* d)){
	branch* _sub = (branch *)sub;
	branch* _obj = (branch *)obj;
	if(data_cmp(_sub->value, _obj->value) == 0)
		return sub;
	if(data_cmp(_sub->value, _obj->value) < 0){
		if(_sub->left == NULL){
			_sub->left = obj;
			_obj->prev = sub;
		}
		else
			branch_insert(_sub->left, obj, data_cmp);
	}
	else{
		if(_sub->right == NULL){
			_sub->right = obj;
			_obj->prev = sub;
		}
		else
			branch_insert(_sub->right, obj, data_cmp);
	}
}
//#define tree_from(x) tree* this_tree = (tree*)x

void tree_insert(struct map* this_map, data* d){
//	tree_from(this_map);
		map_enter* br = branch_create(NULL, NULL, NULL, d);
		map_enter* brret;
		if(((tree*)this_map)->root == NULL)
			((tree*)this_map)->root = br;
		else
			branch_insert(((tree*)this_map)->root, br, ((tree*)this_map)->data_cmp);
}*/

map_enter*  branch_insert(map_enter* sub, map_enter* obj, int (*data_cmp)(data* a, data* d)){
	branch* _sub = (branch *)sub;
	branch* _obj = (branch *)obj;
	if(data_cmp(_sub->value, _obj->value) == 0){
		return sub;
	}
	if(data_cmp(_sub->value, _obj->value) < 0){
		if(_sub->left == NULL){
			_sub->left = obj;
			_obj->prev = sub;
			return NULL;
		}
		else
			return branch_insert(_sub->left, obj, data_cmp);
	}
	else{
		if(_sub->right == NULL){
			_sub->right = obj;
			_obj->prev = sub;
			return NULL;
		}
		else
			return branch_insert(_sub->right, obj, data_cmp);
	}
}
map_enter* tree_insert(struct map* this_map, data* d){
		map_enter* br = branch_create(NULL, NULL, NULL, d);
		if(((tree*)this_map)->root == NULL){
			((tree*)this_map)->root = br;
			return br;
		}
		else{
			map_enter* tbr = branch_insert(((tree*)this_map)->root, br, ((tree*)this_map)->data_cmp);
			if(tbr == NULL)
				return br;
			free(br);
			return tbr;
		}
}

void branch_delete(struct map_enter* br){
	branch * _br = (branch *)br;
	if(_br == NULL)
	 	return;
	branch_delete(_br->left);
	branch_delete(_br->right);
	free(_br);
}
void tree_delete(struct map* this_map){
	branch_delete(((tree*)this_map)->root);
	free((tree*)this_map);
}

struct map_enter* branch_search(struct map_enter * me, data* d, int (*data_cmp)(data* a, data* b)){
	branch* br = (branch*)me;
	if(br == NULL)
		return NULL;
//	printf("LOG SEARCH %d\n", *(int *)(br->value));
	if(data_cmp(br->value, d) == 0)
		return (map_enter *)br;
	if(data_cmp(br->value, d) < 0)
		return branch_search(br->left, d, data_cmp);
	else
		return branch_search(br->right, d, data_cmp);
}
struct map_enter* tree_search(struct map * this_map, data* d){
	return branch_search(((tree*)this_map)->root, d, ((tree*)this_map)->data_cmp);
}
struct map_enter* tree_prev(struct map* this_map, struct map_enter* br){
//	branch * br = (branch *)br;
	map_enter* temp;
	if(((branch *)br)->left != NULL){
		for(temp = ((branch *)br)->left; ((branch *)temp)->right != NULL; temp = ((branch*)temp)->right);
		return temp;
	}
	for(temp = br; ((branch *)temp)->prev != NULL; temp = ((branch *)temp)->prev)
		if( ((branch*)((branch*)temp)->prev)->right == temp)
			return ((branch*)temp)->prev;
	return NULL;		
	//���� � ��� ���� ����� ������
	//	�� ����� ������ ������� ��� �������
	//�����
	//	���� �� ������ ������ ��
	//		����� ��������
	//	�����
	//		���� ������, ����� ��� ������ ����� ������ ������
}
struct map_enter* tree_next(struct map* this_map, struct map_enter* br){
	map_enter* temp;
	if(((branch *)br)->right != NULL){
		for(temp = ((branch *)br)->right; ((branch*)temp)->left != NULL; temp = ((branch*)temp)->left);
		return temp;
	}
	for(temp = br; ((branch *)temp)->prev != NULL; temp = ((branch *)temp)->prev)
		if(((branch *)(((branch *)temp)->prev))->left == temp)
			return ((branch *)temp)->prev;
	return NULL;		
}

void tree_remove(struct map* this_map, struct map_enter* br){
	if(this_map == NULL){
		#ifdef MAP_CHECK
			printf("\nWARNING: THERE IS NO MAP\n");
		#endif
		return;
	}
	if(br == NULL){
		#ifdef BRANCH_CHECK
			printf("\nWARNING: THERE IS NO BRANCH\n");
		#endif
		return;
	}
	map_enter** direct;
	map_enter* temp;
	if(((branch *)br)->prev == NULL)
		direct = &(((tree*)this_map)->root);
	else
		if(((branch*)(((branch *)br)->prev))->right == br)
			direct = &(((branch*)((branch *)br)->prev)->right);
		else
			direct = &(((branch *)((branch *)br)->prev)->left);
	if(((branch *)br)->right != NULL){
		*direct = ((branch *)br)->right;
		((branch *)(((branch *)br)->right))->prev = ((branch *)br)->prev;
		if(((branch *)br)->left != NULL){
			for(temp = ((branch *)br)->right; ((branch *)temp)->left != NULL; temp = ((branch *)temp)->left);
			((branch *)temp)->left = ((branch *)br)->left;
			((branch *)((branch *)br)->left)->prev = temp;
		}
	}
	else{
		if(((branch *)br)->left != NULL){
			*direct = ((branch *)br)->left;
			((branch *)((branch *)br)->left)->prev = ((branch *)br)->prev;
		}else
			*direct = NULL;
	}	
	free(br);
}
struct map_enter* tree_first(struct map* this_map){
	tree* tr = (tree*)this_map;
	map_enter* me = tr->root;
	if(me == NULL)
		return NULL;
	while(((branch*)me)->left != NULL)
		me = ((branch*)me)->left;
	return me;
}
struct map_enter* tree_last(struct map* this_map){
	tree* tr = (tree *)this_map;
	map_enter* me = tr->root;
	if(me == NULL)
		return NULL;
	while(((branch*)me)->right != NULL)
		me = ((branch*)me)->right;
	return me;
}
struct map_enter* tree_end(struct map* this_map){
	return NULL;
}








/*
struct map* hash_create(){
		struct map* m = malloc(sizeof(struct hash));
		m->
}*/




/*br* temp; //OLD
	if(br->prev == NULL)
		((tree*)this_map)->root = br->right;
	else
		if(br->prev->right == br)
			br->prev->right = br->right;
		else
			br->prev->left = br->right;
	if(br->left == NULL)
		return;
	for(temp = br->right; temp->left != NULL; temp = temp->left);//???
	temp->left = br->left;
	temp->left->prev = temp;*/ // OLD
	
	
	
	
	//OLD
	
/*

struct map* tree_create( int (*data_cmp)(data* a, data* b)){
		struct map* m = malloc(sizeof(struct tree));
		m->insert = tree_insert;
		m->full_delete = tree_delete;
		m->search = tree_search;
		m->get_next = tree_next;
		m->get_prev = tree_prev;
		struct tree* tr = (struct tree *)m;
		tr->root = NULL;
		tr->data_cmp = data_cmp;
		return m;
}
void branch_insert(branch* sub, branch* obj, int (*data_cmp)(data* a, data* d)){
	if(data_cmp(sub->value, obj->value) < 0){
		if(sub->left == NULL){
			sub->left = obj;
			obj->prev = sub;
		}
		else
			branch_insert(sub->left, obj, data_cmp);
	}
	else{
		if(sub->right == NULL){
			sub->right = obj;
			obj->prev = sub;
		}
		else
			branch_insert(sub->right, obj, data_cmp);
	}
}
void tree_insert(struct map* this_map, data* d){
		branch* br = branch_create(NULL, NULL, NULL, d);
		if(((tree*)this_map)->root == NULL)
			((tree*)this_map)->root = br;
		else
			branch_insert(((tree*)this_map)->root, br, ((tree*)this_map)->data_cmp);
}
void branch_delete(struct branch* br){
	if(br == NULL)
	 	return;
	branch_delete(br->left);
	branch_delete(br->right);
	free(br);
}
void tree_delete(struct map* this_map){
	branch_delete(((tree*)this_map)->root);
	free((tree*)this_map);
}

struct branch* branch_search(struct branch * br, data* d, int (*data_cmp)(data* a, data* b)){
	if(br == NULL)
		return NULL;
	if(data_cmp(br->value, d) == 1)
		return br;
	if(data_cmp(br->value, d) < 0)
		return branch_search(br->left, d, data_cmp);
	else
		return branch_search(br->right, d, data_cmp);
}
struct branch* tree_search(struct map * this_map, data* d){
	return branch_search(((tree*)this_map)->root, d, ((tree*)this_map)->data_cmp);
}
struct branch* tree_prev(struct map* this_map, struct branch* br){
	branch* temp;
	if(br->left != NULL){
		for(temp = br->left; temp->right != NULL; temp = temp->right);
		return temp;
	}
	for(temp = br; temp->prev != NULL; temp = temp->prev)
		if(temp->prev->right == temp)
			return temp->prev;
	return NULL;		
//	���� � ��� ���� ����� ������
//		�� ����� ������ ������� ��� �������
//	�����
//		���� �� ������ ������ ��
//			����� ��������
//		�����
//			���� ������, ����� ��� ������ ����� ������ ������
}
struct branch* tree_next(struct map* this_map, struct branch* br){
	branch* temp;
	if(br->right != NULL){
		for(temp = br->right; temp->left != NULL; temp = temp->left);
		return temp;
	}
	for(temp = br; temp->prev != NULL; temp = temp->prev)
		if(temp->prev->left == temp)
			return temp->prev;
	return NULL;		
}

void tree_remove(struct map* this_map, struct branch* br){
	if(this_map == NULL){
		#ifdef MAP_CHECK
			printf("\nWARNING: THERE IS NO MAP\n");
		#endif
		return;
	}
	if(br == NULL){
		#ifdef BRANCH_CHECK
			printf("\nWARNING: THERE IS NO BRANCH\n");
		#endif
		return;
	}
	branch** direct;
	branch* temp;
	if(br->prev == NULL)
		direct = &(((tree*)this_map)->root);
	else
		if(br->prev->right == br)
			direct = &(br->prev->right);
		else
			direct = &(br->prev->left);
	if(br->right != NULL){
		*direct = br->right;
		br->right->prev = br->prev;
		if(br->left != NULL){
			for(temp = br->right; temp->left != NULL; temp = temp->left);
			temp->left = br->left;
			br->left->prev = temp;
		}
	}
	else{
		if(br->left != NULL){
			*direct = br->left;
			br->left->prev = br->prev;
		}
		*direct = NULL;
	}	
	free(br);
}*/
//\OLD
