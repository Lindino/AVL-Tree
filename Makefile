all:
	gcc -std=c11 -O0 -Wall avl.c test.c -o main
	./main

clean:
	rm main
