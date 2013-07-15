GTESTPATH=/home/przybyl/Programming/gtest-1.6.0

CC=clang++
CFLAGS=-std=c++11

LFLAGS=$(GTESTPATH)/lib/.libs/
INCLUDE=$(GTESTPATH)/include
LIBS=-lgtest -pthread

OUT=particleSystemTests

test: particleSystemTest.cpp
	$(CC) $(CFLAGS) -L $(LFLAGS) particleSystemTest.cpp -o $(OUT) -I $(INCLUDE) $(LIBS)

clean:
	rm  $(OUT)
