all:
	gcc Dict/dict.c hash.c -o Dict/dict
	gcc Test_Tree/usabilite_test.c tree.c -o Test_Tree/usability_test
clean:
	rm Dict/dict Test_Tree/usability_test
