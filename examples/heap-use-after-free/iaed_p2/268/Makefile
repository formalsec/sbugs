all:
	gcc -fsanitize=address proj2.c -g -o proj2_bug
	gcc -fsanitize=address proj2_fixed.c -g -o proj2_fixed

test_bug:
	./proj2_bug < r_41.in

test_fix:
	./proj2_fixed < r_41.in
