default:
	gcc -Wall -o prog main.c input.c stringWrap.c listArrayList.c listElem.c mapArrayList.c mapElem.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c data/import.c memory.c processing/athleteShow.c
debug:
	gcc -Wall -o prog -g main.c input.c stringWrap.c listArrayList.c listElem.c mapArrayList.c mapElem.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c data/import.c memory.c processing/athleteShow.c
clean:
	rm -f prog
