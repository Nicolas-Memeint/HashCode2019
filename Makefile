CC = clang++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O3
LDFLAGS=-lpthread

all: run

run: main
	sh run.sh

main: main.o

clean:
	rm -rf main.o main out

.PHONY: all run clean
