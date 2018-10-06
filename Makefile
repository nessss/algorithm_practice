CC=g++-8
CFLAGS=-Wall -std=c++17 -O3

%: %.cpp pp.h heap.h
	$(CC) $(CFLAGS) -o $@ $@.cpp

run %: %
	./$@
