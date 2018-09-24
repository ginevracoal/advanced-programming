# SRC = $(shell find . -name '*.cc') #search in all subfolders
SRC = $(wildcard *.cc)
# INC = $(wildcard inc/*.h)
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
DBGFLAGS = -g -D DEBUG
EXE := $(SRC:.cc=.x) 
DBGEXE := $(SRC:.cc=_debug.x)
# STDEXE := $(SRC:.cc=_std.x)

all: $(EXE)

debug: $(DBGEXE)

# std: $(STDEXE)

%.x: %.cc $(INC)
	$(CC) $< -o $@ $(CFLAGS)

%_debug.x: %.cc $(INC)
	$(CC) $< -o $@ $(CFLAGS) $(DBGFLAGS)

clean:
	rm -f $(EXE) $(DBGEXE) $(STDEXE)

.PHONY: clean debug