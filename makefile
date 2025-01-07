all: client server server2
compile: program.o
	@gcc -o program program.o
program.o: program.c
	@gcc -c program.c
run:
	@./program
save:
	@git add --all
	@git commit
	@git push
clean:
	@rm *.o
	@rm program
