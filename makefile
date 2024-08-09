default:
	gcc -Wall -o prog main.c input.c types/athlete.c types/host.c types/medal.c
debug:
	gcc -Wall -o prog -g main.c input.c types/athlete.c types/host.c types/medal.c
clean:
	rm -f prog
