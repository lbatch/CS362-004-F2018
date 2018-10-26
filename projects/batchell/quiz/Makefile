CFLAGS= -Wall -fpic -coverage -lm -std=c99

all: testme
	
testme: testme.c
	gcc $(CFLAGS) -o testme testme.c
	./testme

clean:
	rm -rf testme *.gcov *.gcda *.gcno *.o
