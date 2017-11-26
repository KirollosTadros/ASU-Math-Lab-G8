CC = g++
CFLAGS = -std=c++0x
LDFLAGS =


all: matrix

matrix: MyMatrix.o main.o
	$(CC) $(LDFLAGS) $^ -o $@

MyMatrix.o: MyMatrix.cpp MyMatrix.h
	$(CC) $(CFLAGS) -c MyMatrix.cpp -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -f *.o *.out
