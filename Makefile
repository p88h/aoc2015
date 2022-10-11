CXX := clang++
SRCS := $(wildcard day*.cc)
OBJS := $(SRCS:.cc=.o)
EXES := $(SRCS:.cc=)
CXXFLAGS := -std=c++11 -O -g

all: $(EXES)

clean: 
	rm -f $(EXES) *.o

$(EXES): %: %.o common.o
	$(CXX) -o $@ $^

