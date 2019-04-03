PROGRAM_NAME = TextQuery
CXX = g++

SRCDIR = src
SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(patsubst %c,%o,$(SOURCES))

rm = rm -f

TextQuery:
	g++ -Wall -c -Isrc src/main.cpp -std=c++11
	g++ -Wall -c -Isrc src/query.cpp -std=c++11
	g++ main.o query.o -o TextQuery -std=c++11

clean:
	rm *.o
	rm TextQuery
