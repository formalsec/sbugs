all:
	gcc -fsanitize=address v3.c -g -o bug

test_bug:
	./bug < random_598.in