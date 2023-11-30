all:
	gcc -fsanitize=address proj1.c -g -o bug
	gcc -fsanitize=address teste.c -g -o bug2

test_bug:
	./bug < random_629.in

test_bug2:
	./bug2 < random_2070.in