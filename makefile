CC = g++
IDIR = include 
SRC_DIR = src
BUILD_DIR = build
CFLAGS = -Wall -g  -I$(IDIR) -std=c++11
#MAKEFLAGS =+ --silent

main: main.o
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/main main.o
	@echo Made objects.

main.o: $(SRC_DIR)/main.cc 
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cc
	@echo Compiled source.

clean:
	@-rm -f *.o core *.core
	@echo Clean.
