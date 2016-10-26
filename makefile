list: random.c
	gcc random.c -o random

run: random
	./random

clean:
	rm *~
