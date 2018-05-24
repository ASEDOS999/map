#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tree.h"
#include "../hash.h"
#include "../GOOGLETEST/googletest/include/gtest/gtest.h"
#define to_tree(x) tree* tr = (tree*)x
#define to_branch(x) branch* br = (branch*)x
#define LEN 80
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

int hashing_string(data* key)
{
	char* s = (char*)key;
	int sum = 0, i;
	for(i = 0; i < LEN; i++)
        	sum = sum + s[i];
	return sum;
}

int key_equal_string(data* key1, data* key2)
{
	return !(strcmp((char*)key1, (char*)key2));
}

int hashing_int(data* key)
{
	int s = (*(int*)key);
	return s;
}

int key_equal_int(data* key1, data* key2)
{
	if((key1 == NULL) || (key2 == NULL))
		return 0;
	int s1 = (*(int*)key1);
	int s2 = (*(int*)key2);
	return (s1 == s2);
}


namespace {

TEST(HashTest, create){
	map* hash = hash_create(hashing_string, key_equal_string);
	ASSERT_FALSE(hash == NULL);
	EXPECT_TRUE(hash->first(hash) == hash->last(hash));
	EXPECT_TRUE(hash->first(hash) == hash->end(hash));
	EXPECT_TRUE(hash->first(hash) == NULL);
	hash->delet(hash);
}

TEST(HashTest, insert_string){
	map* hash = hash_create(hashing_string, key_equal_string);
	char* s = "Hello";
	map_enter* u = hash->insert(hash, (data*)s);
	EXPECT_STREQ(s, (char*)(u->get_val(u)));
	hash->delet(hash);
}

TEST(HashTest, insert_int){
	map* hash = hash_create(hashing_int, key_equal_int);
	int *s;
	(*s)= 135;
	map_enter* u = hash->insert(hash, (data*)s);
	EXPECT_EQ(s, (((int*)(u->get_val(u)))));
	hash->delet(hash);
}

TEST(HashTest, first){
	map* hash = hash_create(hashing_int, key_equal_int);
	int s =135;
	map_enter* u1 = hash->insert(hash, (data*)(&s));
	map_enter* u2 = hash->first(hash);
	EXPECT_EQ(u1, u2);
	hash->delet(hash);
}

TEST(HashTest, last){
	map* hash = hash_create(hashing_int, key_equal_int);
	int s =135;

	map_enter* u1 = hash->insert(hash, (data*)(&s));
	map_enter* u2 = hash->last(hash);
	EXPECT_EQ(u1, u2);
	hash->delet(hash);
}

TEST(HashTest, not_unique_insert){
	map* hash = hash_create(hashing_int, key_equal_int);
	int s1 = 135, s2 = 135;

	map_enter* u = hash->insert(hash, (data*)(&s1));
	EXPECT_EQ(&s1, (((int*)(u->get_val(u)))));
	u = hash->insert(hash, (data*)(&s2));
	EXPECT_TRUE(u == NULL);
	hash->delet(hash);
}

TEST(HashTest, next){
	map* hash = hash_create(hashing_int, key_equal_int);
	int s = 135;
	map_enter* u = hash->insert(hash, (data*)(&s));
	EXPECT_EQ(&s, (((int*)(u->get_val(u)))));
	u = hash->get_next(hash, u);
	EXPECT_TRUE(u == NULL);
	hash->delet(hash);
}

TEST(HashTest, search){
	map* hash = hash_create(hashing_int, key_equal_int);
	int s = 135;
	map_enter* u = hash->insert(hash, (data*)(&s));
	EXPECT_EQ(&s, (((int*)(u->get_val(u)))));
	u = hash->search(hash, (data*)(&s));
	EXPECT_EQ(&s, (((int*)(u->get_val(u)))));
	hash->delet(hash);
}


TEST(HashTest, search_many_data){
	map* hash = hash_create(hashing_int, key_equal_int);
	int s = 135;
	int i;
	map_enter* u;
	for(i = 0; i < H; i++)
	{
		int* m = (int*)malloc(sizeof(int));
		(*m) = i;
		u = hash->insert(hash, (data*)m);
	}
	u = hash->search(hash, (data*)(&s));
	EXPECT_EQ(s, (*(((int*)(u->get_val(u))))));
	hash->delet(hash);
}



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
	EXPECT_TRUE(m->first(m) == tme);
        EXPECT_TRUE(m->first(m) == m->last(m));
	EXPECT_FALSE(m->first(m) == m->end(m));
	EXPECT_FALSE(m->first(m) == NULL);
	m->remove(m, tme);
        ASSERT_TRUE(m->first(m) == m->last(m));
        ASSERT_TRUE(m->first(m) == m->end(m));
	ASSERT_TRUE(m->first(m) == NULL);
	tme = m->insert(m, ((data*)(mass)));
	ASSERT_TRUE(m->first(m) == tme);
        ASSERT_TRUE(m->first(m) == m->last(m));
        ASSERT_FALSE(m->first(m) == m->end(m));
        ASSERT_FALSE(m->first(m) == NULL);
	m->delet(m);
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
	m->delet(m);
}
TEST (RootTests, RootGet_nextGet_prev){
        map* m = tree_create(int_cmp);
        m->insert(m, ((data*)(mass)));
	EXPECT_TRUE(m->get_next(m, m->first(m)) == m->end(m));
        EXPECT_TRUE(m->get_prev(m, m->first(m)) == m->end(m));
        m->delet(m);
}
TEST (StraightTreeTests, LeftTree){
	map* m = tree_create(int_cmp);
	map_enter* tme;
	int i;
	for(i = 0; i > -5; i = i - 1){
		m->insert(m, ((data*)(mass + i)));
	}
	i = - 4;
	for(tme = m->first(m); tme != m->end(m); tme = m->get_next(m, tme)){
		EXPECT_EQ(*(mass + i), *((int *)(tme->get_val(tme))));
		++i;
	}
	EXPECT_EQ(1, i);
	i = 0;
	for(tme = m->last(m); tme != m->end(m); tme = m->get_prev(m, tme)){
                EXPECT_EQ(*(mass + i), *((int *)(tme->get_val(tme))));
                i = i - 1;
        }
	EXPECT_EQ(-5, i);
	tme = m->search(m, (data*)(mass - 3));
	ASSERT_FALSE(tme == NULL);
	EXPECT_EQ(*(mass - 3), *((int*)(tme->get_val(tme))));
	m->remove(m, tme);
	tme = m->search(m, (data*)(mass - 3));
	ASSERT_TRUE(tme == NULL);
	i = - 4;
        for(tme = m->first(m); tme != m->end(m);/* tme = m->get_next(m, tme)*/){
		if(i != -3){
                	EXPECT_EQ(*(mass + i), *((int *)(tme->get_val(tme))));
			tme = m->get_next(m, tme);
		}
                ++i;
        }
        m->delet(m);
}
TEST(StraightTreeTests, RightTree){
        map* m = tree_create(int_cmp);
        map_enter* tme;
        int i;
        for(i = 0; i < 5; i = i + 1){
                m->insert(m, ((data*)(mass + i)));
        }
        i = 0;
        for(tme = m->first(m); tme != m->end(m); tme = m->get_next(m, tme)){
                EXPECT_EQ(*(mass + i), *((int *)(tme->get_val(tme))));
                ++i;
        }
        EXPECT_EQ(5, i);
        i = 4;
        for(tme = m->last(m); tme != m->end(m); tme = m->get_prev(m, tme)){
                EXPECT_EQ(*(mass + i), *((int *)(tme->get_val(tme))));
                i = i - 1;
        }
        EXPECT_EQ(-1, i);
        tme = m->search(m, (data*)(mass + 3));
        ASSERT_FALSE(tme == NULL);
        EXPECT_EQ(*(mass + 3), *((int*)(tme->get_val(tme))));
        m->remove(m, tme);
        tme = m->search(m, (data*)(mass + 3));
        ASSERT_TRUE(tme == NULL);
        i = 0;
        for(tme = m->first(m); tme != m->end(m); /*tme = m->get_next(m, tme)*/){
                if(i != 3){
                        EXPECT_EQ(*(mass + i), *((int *)(tme->get_val(tme))));
			tme = m->get_next(m, tme);
                }
                ++i;
        }
        m->delet(m);
}
TEST(ComplexTreeTests, CompexTest){
	int i;
	map* m = tree_create(int_cmp);
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
        for(tme = m->first(m); tme != m->end(m); tme = m->get_next(m, tme)){
                EXPECT_EQ(*(_mass + i), *((int *)(tme->get_val(tme))));
                ++i;
        }
     	EXPECT_EQ(11, i);
        i = 10;
        for(tme = m->last(m); tme != m->end(m); tme = m->get_prev(m, tme)){
                EXPECT_EQ(*(_mass + i), *((int *)(tme->get_val(tme))));
                i = i - 1;
        }
	EXPECT_EQ(-1, i);
	tme = m->search(m, (data*)(_mass + 4));
	ASSERT_FALSE(tme == NULL);
	m->remove(m, tme);
	i = 0;
	for(tme = m->first(m); tme != m->end(m); /*tme = m->get_next(m, tme)*/){
                if(i != 4){
			EXPECT_EQ(*(_mass + i), *((int *)(tme->get_val(tme))));
			tme = m->get_next(m, tme);
		}
                i = i + 1;
        }
	tme = m->search(m, (data*)(_mass + 0));
        ASSERT_FALSE(tme == NULL);
        m->remove(m, tme);
        i = 0;
        for(tme = m->first(m); tme != m->end(m); /*tme = m->get_next(m, tme)*/){
                if((i != 4) && (i != 0)){
                        EXPECT_EQ(*(_mass + i), *((int *)(tme->get_val(tme))));
			tme = m->get_next(m, tme);
		}
                i = i + 1;
        }
 	tme = m->search(m, (data*)(_mass + 5));
        ASSERT_FALSE(tme == NULL);
        m->remove(m, tme);
        i = 0;
        for(tme = m->first(m); tme != m->end(m); /*tme = m->get_next(m, tme)*/){
                if((i != 4) && (i != 0) && (i != 5)){
                        EXPECT_EQ(*(_mass + i), *((int *)(tme->get_val(tme))));
			tme = m->get_next(m, tme);
		}
                i = i + 1;
        }
	m->delet(m);
}

}
