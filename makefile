default:
	gcc -Wall -o prog main.c utilities/input.c utilities/stringWrap.c adts/listArrayList.c adts/listElem.c adts/mapArrayList.c adts/mapElem.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c data/import.c utilities/memory.c shows/simple.c
debug:
	gcc -Wall -o prog -g main.c utilities/input.c utilities/stringWrap.c adts/listArrayList.c adts/listElem.c adts/mapArrayList.c adts/mapElem.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c data/import.c utilities/memory.c shows/simple.c
clean:
	rm -f prog
