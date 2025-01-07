all: client server server2
compile: program.o
	@gcc -o program program.o
program.o: program.c
	@gcc -c program.c
run:
	@./program
save:
	@git add *.c *.h makefile *.md
	@git commit
	@git push
	@clear
	@echo saved and pushed
clean:
	@rm *.o
	@rm program
