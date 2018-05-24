#include"../hash.h"
#include"../googletest/googletest/include/gtest/gtest.h"

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


namespace {

TEST(HashTest, insert){
	//Test of string's insert
	map* hash = hash_create(hashing_string, key_equal_string);
	char* s = "Hello";
	map_enter* u = hash->insert(hash, (data*)s);
	EXPECT_STREQ(s, (char*)(u->get_val(u)));
}

}
