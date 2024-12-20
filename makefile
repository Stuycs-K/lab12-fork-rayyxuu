.PHONY: run clean compile
compile main: main.o
	@gcc -o main main.o

main.o: main.c
	@gcc -c main.c

run: main
	@./main

clean:
	@rm *.o
	@rm main