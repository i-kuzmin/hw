
SRC = $(wildcard *.cpp)
HDR = $(wildcard *.h)

PROGRAM = hw

CXX=clang++ -c
CXXFLAGS+=-std=c++11 -g

LD=clang++
LDFLAGS+=-lstdc++

LIBS =-lboost_regex
OBJS = $(SRC:%.cpp=%.o)
DEPS = $(SRC:%.cpp=%.dep)

%.dep: %.cpp
	$(CXX) $(CXXFLAGS) $< -M -o $@

$(foreach i, $(SRC), $(eval -include $(i:%.cpp=%.dep)))

$(PROGRAM): $(OBJS)
	$(LD) $(LDDFLAGS) -o $@ $(LIBS) $^

all: $(PROGRAM) 

clean:
	rm $(OBJS) $(PROGRAM) $(DEPS)

.SUFFIXES: .o .cpp .cpp .dep
.PHONY: run all clean compile

compile: $(OBJS)

run: $(PROGRAM)
	./$^ /00ff test.bin

.DEFAULT_GOAL := $(PROGRAM)

