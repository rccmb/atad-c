default:
	gcc -Wall -o prog main.c input.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c
debug:
	gcc -Wall -o prog -g main.c input.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c
clean:
	rm -f prog
