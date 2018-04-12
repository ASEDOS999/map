#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tree.h"
#define to_tree(x) tree* tr = (tree*)x
#define to_branch(x) branch* br = (branch*)x
int int_cmp(data* a, data* b){
        if(*(int*)a < *(int*)b)
                return 1;
        if(*(int*)a == *(int*)b)
                return 0;
        return -1;
}
int _mass[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int* mass = _mass + 5;
//int mass[] = {6, 4, 7, 1, 5, 9, 0, 8, 10};
int create_delete_test(){
	map* m = tree_create(int_cmp);
	to_tree(m);
	if (tr == NULL)
		return 1;
	tr->delet(m);
	return 0;
}
int root_test(){
	map* m = tree_create(int_cmp);
	to_tree(m);
	map_enter* tme = tr->insert(m, ((data*)(mass)));
	if((tr->root == NULL) || (((branch*)(tr->root))->value != (data*)mass))
		return 1;
	map_enter* me = tr->search(m, (data*)mass);
	if((me != tme) || (me == NULL))
		return 2;
	if(tr->last(m) != tr->first(m))
		return 3;
	if(tr->last(m) != me)
		return 4;
	if(tr->get_next(m, me) != tr->get_prev(m, me))
		return 5;

	//if((tr->get_prev(m, me) != tr->end(m)) || (tr->get_prev(m, me) != tr->end(m)))
	//	return 0;
	//if((tr->first(m) != me) || (tr->last(m) != me))
          //      return 0;
	tr->remove(m, tr->search(m, (data*)mass));
	if(tr->root != NULL)
                return 6;
	if((tr->first(m) != tr->last(m)) || (tr->last(m) != NULL))
		return 7;
        tr->delet(m);
	return 0;
}
int insert_test(){
	map* m = tree_create(int_cmp);
        to_tree(m);
        map_enter* rt = tr->insert(m, (data*)mass);
	map_enter* r = tr->insert(m, (data*)(mass + 1));
	map_enter* l = tr->insert(m, (data*)(mass - 1));
	if(((branch*)r)->value != (data*)(mass + 1))
		return 1;
	if(((branch*)l)->value != (data*)(mass - 1))
                return 2;
	to_branch(rt);
	if((br->left != l)||(br->right != r))
		return 3;
	if((((branch*)r)->prev != rt) || (((branch*)l)->prev != rt))
                return 4;
	map_enter* rr = tr->insert(m, (data*)(mass + 2));
        map_enter* ll = tr->insert(m, (data*)(mass - 2));
	if((((branch*)r)->right != rr) || (((branch*)l)->left != ll))
                return 5;
	tr->delet(m);
	return 0;
}		
int search_test(){
	map* m = tree_create(int_cmp);
        to_tree(m);
        tr->insert(m, (data*)(mass));
        map_enter* r = tr->insert(m, (data*)(mass + 1));
        map_enter* l = tr->insert(m, (data*)(mass - 1));
	//if(r == NULL)
        //        printf("\nNULL\n");
        //else printf("\n %d \n", *((int*)(((branch*)(r))->value)));
	
	//if(tr->search(m, (data*)(mass + 1)) == NULL)
        //        printf("\nNULL\n");
        // else printf("\n %d \n", *((int*)(((branch*)(tr->search(m, (data*)(mass + 1))))->value)));
	
	//printf("search %d r%d\n",tr->search(m, (data*)(mass + 1)), r);
	
	if(r != tr->search(m, (data*)(mass + 1)))
                return 1;
	if(l != tr->search(m, (data*)(mass - 1)))
		return 2;
	return 0;
}
int remove_test(){
        map* m = tree_create(int_cmp);
        to_tree(m);
        map_enter* rt = tr->insert(m, (data*)(mass));
	to_branch(rt);
        map_enter* r = tr->insert(m, (data*)(mass + 1));//case1
	tr->remove(m, r);
	if(br->right != NULL)
		return 1;
        map_enter* l = tr->insert(m, (data*)(mass - 1));//case2 root !=NULL
	tr->remove(m, l);
        if(br->left != NULL)
                return 2;
        r = tr->insert(m, (data*)(mass + 1));//case3 root != NULL
	tr->remove(m, rt);
	if((tr->root != r) || (((branch*)r)->prev != NULL))
		return 3;
	tr->remove(m, r);
	rt = tr->insert(m, (data*)(mass));//case4
	l = tr->insert(m, (data*)(mass - 1));
        tr->remove(m, tr->root);
	//printf("\n case 4\n");
	//if(tr->root == NULL)
	//	printf("\nNULL\n");
	//else printf("\n %d \n", *((int*)(((branch*)(tr->root))->value)));
        if((tr->root != l))
		return 4;
	if (((branch*)l)->prev != NULL)
                return 5;
	tr->remove(m, tr->root);
	rt = tr->insert(m, (data*)(mass));//case 5
	r = tr->insert(m, (data*)(mass + 2));
        l = tr->insert(m, (data*)(mass - 1));
	map_enter* rl = tr->insert(m, (data*)(mass + 1));
	tr->remove(m, rt);
	if(((branch*)rl)->left != l)
		return 6;
	if(((branch*)l)->prev != rl)
		return 7;
	tr->delet(m);
        return 0;
}
int get_next_get_prev_test(){
	map* m = tree_create(int_cmp);
        to_tree(m);
      	//map_enter* rt = tr->insert(m, (data*)(mass));
	int i;
	for(i = -5; i <= 5; ++i){
		tr->insert(m, (data*)(mass + i));
	}
	//map_enter* iter = tr->first(m);
	//printf("\ninfront go test\n");
	i = -5;
	map_enter* iter;
	for( iter = tr->first(m); iter != tr->end(m); iter = tr->get_next(m, iter)){
		if(((branch*)iter)->value != (data*)(mass + i)){
			 printf("\niter %d  data %d \n", 
				*((int*)(((branch*)iter)->value)), 
				*(mass + i));
			return i + 1;
		}
		++i;
	}
	i = 5;
	for( iter = tr->last(m); iter != tr->end(m); iter = tr->get_prev(m, iter)){
                if(((branch*)iter)->value != (data*)(mass + i)){
                         printf("\niter %d  data %d \n",
                                *((int*)(((branch*)iter)->value)),
                                *(mass + i));
			return -i - 1;
		}
        	i = i - 1;
        }
	tr->delet(m);
	return 0;
}
int main(){
	int i;
	printf("create_delete_test " );
	i = create_delete_test();
	if(i == 0)
		printf("Sucssed \n" );
	else	
		printf("Failed: error number == %d\n", i);

	printf("root_test " );
	i = root_test();
	if(i == 0)
		printf("Sucssed \n" );
	else
		printf("Failed: error number == %d\n", i);
	printf("insert_test " );
	i = insert_test();
	if(i == 0)
		printf("Sucssed \n" );
	else
		printf("Failed: error number == %d\n", i);
	printf("search_test " );
	i = search_test();
	if(i == 0)
		printf("Sucssed \n" );
	else
		printf("Failed: error number == %d\n", i);
	printf("remove_test " );
	i = remove_test();
	if(i == 0)
		printf("Sucssed \n" );
	else
		printf("Failed: error number == %d\n", i);
	printf("get_next_get_prev_test " );
	i = get_next_get_prev_test();
        if(i == 0)
                printf("Sucssed \n" );
        else
                printf("Failed: error number == %d\n", i);
	return 0;
}
