spellcheck.exe: spellcheck.o hash.o
	g++ -o spellcheck.exe spellcheck.o hash.o

spellcheck.o: spellcheck.cpp hash.h
	g++ -c -std=c++11 spellcheck.cpp

hash.o: hash.cpp hash.h
	g++ -c -std=c++11 hash.cpp

clean:
	rm *.exe *.o *.stackdump *~

