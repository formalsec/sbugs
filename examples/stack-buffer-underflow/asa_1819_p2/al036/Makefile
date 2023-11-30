all:
	gcc -fsanitize=address Asa2.c -g -o bug

test_bug:
	./bug < random_129.in