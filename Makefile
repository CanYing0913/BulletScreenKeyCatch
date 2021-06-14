EXENAME = mc
OBJS = main.o

CXX = clang++
CXXFLAGS = # -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = #-std=c++1y -stdlib=libc++ -lc++abi -lm


.PHONY: all clean

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) -o $(EXENAME)

main.o : main.cpp zalg.h
	$(CXX) -c -g main.cpp -o $(OBJS)

clean :
	-rm -f *.o $(EXENAME)
	rm -f *_find.txt
