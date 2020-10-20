dijkstra.exe: dijkstra.o graph.o heap.o hash.o
	g++ -o dijkstra.exe graph.o dijkstra.o heap.o hash.o

dijkstra.o: dijkstra.cpp
	g++ -c -std=c++11 dijkstra.cpp

graph.o: graph.cpp graph.h
	g++ -c -std=c++11 graph.cpp

heap.o: heap.cpp heap.h
	g++ -c -std=c++11 heap.cpp

hash.o: hash.cpp hash.h
	g++ -c -std=c++11 hash.cpp

debug:
	g++ -g -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
