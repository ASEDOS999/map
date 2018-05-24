#include"../hash.h"
#include"../GOOGLETEST/googletest/include/gtest/gtest.h"

#define LEN 80

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
}
