
SRC = $(wildcard *.cpp)
PROGRAM = hw
CXX=clang++ -g
LDFLAGS+=
#-stdlib=libc++ 
$(PROGRAM): $(SRC)
	$(CXX) -o $@ -std=c++11 -lstdc++ $^

all: $(PROGRAM) 

.SUFFIXES:
.PHONY: run all

run: $(PROGRAM)
	./$^ plane 

.DEFAULT_GOAL := $(PROGRAM)

