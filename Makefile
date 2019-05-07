CC = g++
CFLAGS = -std=c++11 -Wall -pedantic -ggdb

.PHONY: as clean

as:
	$(CC) $(CFLAGS) as.cpp line.cpp instruction.cpp helper.cpp -o as

clean:
	rm -f as.o as