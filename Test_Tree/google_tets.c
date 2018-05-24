#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tree.h"
#include "../googletest-master/googletest/include/gtest/gtest.h"
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
int asorts[] = {5, 2, 0, 1, 4, 3, 8, 7, 6, 9, 10};
//int mass[] = {6, 4, 7, 1, 5, 9, 0, 8, 10};

TEST(CreateTest, TreeCreateDelete){
	map* m = tree_create(int_cmp);
        ASSERT_FALSE(m == NULL);
	EXPECT_TRUE(m->first(m) == m->last(m));
	EXPECT_TRUE(m->first(m) == m->end(m));
	EXPECT_TRUE(m->first(m) == NULL);
        m->delet(m);
}
TEST(RootTests, RootInsertRemove){
        map* m = tree_create(int_cmp);
        map_enter* tme = m->insert(m, ((data*)(mass)));
	ASSERT_FALSE(tme == NULL);
	EXPECT_EQ(*mass, *((int*)(tme->get_val(tme))));
	map_enter* tme2 = m->insert(m, ((data*)(mass)));
	EXPECT_TRUE(tme2 == NULL);
	m->remove(m, tme);
	EXPECT_TRUE(m->first(m) == m->last(m));
        EXPECT_TRUE(m->first(m) == m->end(m));
        EXPECT_TRUE(m->first(m) == NULL);
	tme = m->insert(m, ((data*)(mass)));
	EXPECT_EQ(*mass, *((int*)(tme->get_val(tme))));
        m->delet(m);
}
TEST(RootTests, RootBeginEnd){
	map* m = tree_create(int_cmp);
        map_enter* tme = m->insert(m, ((data*)(mass)));
	ASSERT_TRUE(m->first(m) == tme);
        ASSERT_TRUE(m->first(m) == m->last(m));
	ASSERT_FALSE(m->first(m) == m->end(m));
	ASSERT_FALSE(m->first(m) == NULL);
	m->remove(m, tme);
	ASSERT_TRUE(m->first(m) == tme);
        ASSERT_TRUE(m->first(m) == m->last(m));
        ASSERT_TRUE(m->first(m) == m->end(m));
	ASSERT_TRUE(m->first(m) == NULL);
	tme = m->insert(m, ((data*)(mass)));
	ASSERT_TRUE(m->first(m) == tme);
        ASSERT_TRUE(m->first(m) == m->last(m));
        ASSERT_FALSE(m->first(m) == m->end(m));
        ASSERT_FALSE(m->first(m) == NULL);
	m->delete(m);
}
TEST(RootTests, RootSearch){
        map* m = tree_create(int_cmp);
        map_enter* tme = m->insert(m, ((data*)(mass)));
	map_enter* tme2 = m->search(m, ((data*)(mass + 1)));
        EXPECT_TRUE(tme2 == NULL);
	tme2 = m->search(m, ((data*)(mass)));
	ASSERT_FALSE(tme2 == NULL);
	EXPECT_EQ(*mass,*((int *)(tme2->get_val(tme2))));
	m->remove(m, tme);
	tme2 = m->search(m, ((data*)(mass)));
	EXPECT_TRUE(tme2 == NULL);
	m->delete(m);
}
TEST (RootTests, RootGet_nextGet_prev){
        map* m = tree_create(int_cmp);
        map_enter* tme = m->insert(m, ((data*)(mass)));
	EXPECT_TRUE(m->get_next(m, m->first(m)) == m->end(m));
        EXPECT_TRUE(m->get_prev(m, m->first(m)) == m->end(m));
        m->delete(m);
}
TEST (StraightTreeTests, LeftTree){
	map* m = tree_create(int_cmp);
	map_enter* tme;
	int i;
	for(i = 0; i > -5; i = i - 1){
		m->insert(m, ((data*)(mass + i)));
	}
	i = - 4;
	for(tme = m->first(m); tme != m->end(m); tme = tme->get_next(m, tme)){
		EXPECT_EQ(*(mass + i), *((int *)(tme->getval(m, tme))));
		++i;
	}
	EXPECT_EQ(1, i);
	i = 0;
	for(tme = m->last(m); tme != m->end(m); tme = tme->get_prev(m, tme)){
                EXPECT_EQ(*(mass + i), *((int *)(tme->getval(m, tme))));
                i = i - 1;
        }
	EXPECT_EQ(-5, i);
	tme = m->search(m, (data*)(mass - 3));
	ASSERT_FALSE(tme == NULL);
	EXPECT_EQ(*(mass - 3), ((int*)(tme->getval(tme))));
	m->remove(m, tme);
	tme = m->search(m, (data*)(mass - 3));
	ASSERT_TRUE(tme == NULL);
	i = - 4;
        for(tme = m->first(m); tme != m->end(m); tme = tme->get_next(m, tme)){
		if(i != -3){
                	EXPECT_EQ(*(mass + i), *((int *)(tme->getval(m, tme))));
		}
                ++i;
        }
        m->delete(m);
}
TEST(StraightTreeTests, RightTree){
        map* m = tree_create(int_cmp);
        map_enter* tme;
        int i;
        for(i = 0; i < 5; i = i + 1){
                m->insert(m, ((data*)(mass + i)));
        }
        i = 0;
        for(tme = m->first(m); tme != m->end(m); tme = tme->get_next(m, tme)){
                EXPECT_EQ(*(mass + i), *((int *)(tme->getval(m, tme))));
                ++i;
        }
        EXPECT_EQ(5, i);
        i = 4;
        for(tme = m->last(m); tme != m->end(m); tme = tme->get_prev(m, tme)){
                EXPECT_EQ(*(mass + i), *((int *)(tme->getval(m, tme))));
                i = i - 1;
        }
        EXPECT_EQ(-1, i);
        tme = m->search(m, (data*)(mass + 3));
        ASSERT_FALSE(tme == NULL);
        EXPECT_EQ(*(mass + 3), ((int*)(tme->getval(tme))));
        m->remove(m, tme);
        tme = m->search(m, (data*)(mass + 3));
        ASSERT_TRUE(tme == NULL);
        i = 0;
        for(tme = m->first(m); tme != m->end(m); tme = tme->get_next(m, tme)){
                if(i != 3){
                        EXPECT_EQ(*(mass + i), *((int *)(tme->getval(m, tme))));
                }
                ++i;
        }
        m->delete(m);
}
TEST(ComplexTreeTests, CompexTest){
	int i;
	map_enter* tme;
	for(i = 0; i < 11; ++i){
                m->insert(m, ((data*)(asorts + i)));
        }
/*
              5
            /   \
         2         8
       /   \     /   \
     0      4   7     9
      \    /   /       \
       1  3   6        10 
		
*/
	i = 0;
        for(tme = m->first(m); tme != m->end(m); tme = tme->get_next(m, tme)){
                EXPECT_EQ(*(_mass + i), *((int *)(tme->getval(m, tme))));
                ++i;
        }
     	EXPECT_EQ(1, i);
        i = 10;
        for(tme = m->last(m); tme != m->end(m); tme = tme->get_prev(m, tme)){
                EXPECT_EQ(*(_mass + i), *((int *)(tme->getval(m, tme))));
                i = i - 1;
        }
	EXPECT_EQ(-1, i);
	tme = m->search(m, (data*)(_mass + 4));
	ASSERT_FALSE(tme == NULL);
	m->remove(m, tme);
	i = 0;
	for(tme = m->first(m); tme != m->end(m); tme = tme->get_next(m, tme)){
                if(i != 4)
			EXPECT_EQ(*(_mass + i), *((int *)(tme->getval(m, tme))));
                i = i + 1;
        }
	tme = m->search(m, (data*)(_mass + 0));
        ASSERT_FALSE(tme == NULL);
        m->remove(m, tme);
        i = 0;
        for(tme = m->first(m); tme != m->end(m); tme = tme->get_next(m, tme)){
                if((i != 4) && (i != 0))
                        EXPECT_EQ(*(_mass + i), *((int *)(tme->getval(m, tme))));
                i = i + 1;
        }
 	tme = m->search(m, (data*)(_mass + 5));
        ASSERT_FALSE(tme == NULL);
        m->remove(m, tme);
        i = 0;
        for(tme = m->first(m); tme != m->end(m); tme = tme->get_next(m, tme)){
                if((i != 4) && (i != 0) && (i != 5))
                        EXPECT_EQ(*(_mass + i), *((int *)(tme->getval(m, tme))));
                i = i + 1;
        }
	m->delete();
}
int main(int ac, char ** av)
{
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
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
        //      printf("\nNULL\n");
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
*/
/*
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
*/
