all:
	gcc -fsanitize=address p2.c -g -o bug

test_bug:
	./bug < random_937.in