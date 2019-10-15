CFLAGS = -c -I$(HOME)/Programming/include
LFLAGS = -L$(HOME)/Programming/lib
LIBS = -ldataStructures

project2: main.o fraction.o
	g++ -o project2 $(LFLAGS) main.o fraction.o $(LIBS)

main.o: main.cc fraction.h stack.h
	g++ $(CFLAGS) main.cc

fraction.o: fraction.cc fraction.h
	g++ $(CFLAGS) fraction.cc