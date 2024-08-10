default:
	gcc -Wall -o prog main.c input.c logic.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c data/import.c commands/memory.c
debug:
	gcc -Wall -o prog -g main.c input.c logic.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c data/import.c commands/memory.c
clean:
	rm -f prog
