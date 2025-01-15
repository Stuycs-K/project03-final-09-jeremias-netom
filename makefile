all: client server server2
compile: program.o client.o host.o
	@gcc -o program program.o host.o client.o
program.o: program.c host.h client.h
	@gcc -c program.c
client.o: client.c client.h
	@gcc -c client.c
host.o: host.c
	@gcc -c host.c
run:
	@./program
save:
	@git add *.c *.h makefile *.md
	@git commit
	@git push
	@clear
	@echo saved and pushed
pulsar:
	@pulsar *.c *.h makefile
clean:
	@rm *.o
	@rm program
