all: test1 t2 test1.2 t2.2

test1: test1.c
	gcc test1.c -o test1 -lgomp

t2: test2.c
	gcc test2.c -o t2 -lgomp

test1.2: test1.2.c
	gcc test1.2.c -o test1.2 -lgomp

t2.2: test2.2.c
	gcc test2.2.c -o t2.2 -lgomp