CC=g++-8
CFLAGS=-Wall -std=c++17 -O3

%: %.cpp pp.h
	$(CC) $(CFLAGS) -o $@ $@.cpp

run %: %
	./$@
