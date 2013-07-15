GTESTPATH=/home/przybyl/Programming/gtest-1.6.0
PROJECTPATH=/home/przybyl/Programming/particle

CC=clang++
CFLAGS=-std=c++11

LFLAGS=-L$(GTESTPATH)/lib/.libs/
INCLUDE=-I$(GTESTPATH)/include -I$(PROJECTPATH) 
LIBS=-lgtest -pthread

TESTOUT=particleSystemTests
BINOUT=main

test: particleSystemTest.cpp
	$(CC) $(CFLAGS) $(LFLAGS) particleSystemTest.cpp -o $(TESTOUT) $(INCLUDE) $(LIBS)

main: main.cpp 
	$(CC) $(CFLAGS) main.cpp -o $(BINOUT) -I$(PROJECTPATH)

clean:
	rm  $(TESTOUT) $(BINOUT)
