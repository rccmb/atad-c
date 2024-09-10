default:
	gcc -Wall -o prog main.c utilities/input.c types/medalAccumulator.c types/athleteMedals.c types/stringWrap.c types/datetime.c shows/complex.c adts/setElem.c adts/setOpenAddressing.c adts/listArrayList.c adts/listElem.c adts/mapArrayList.c adts/mapElem.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c data/import.c data/memory.c shows/simple.c
debug:
	gcc -Wall -o prog -g main.c utilities/input.c types/medalAccumulator.c types/athleteMedals.c types/stringWrap.c types/datetime.c shows/complex.c adts/setElem.c adts/setOpenAddressing.c adts/listArrayList.c adts/listElem.c adts/mapArrayList.c adts/mapElem.c types/athlete.c types/host.c types/medal.c utilities/ui.c utilities/helper.c data/import.c data/memory.c shows/simple.c
clean:
	rm -f prog
