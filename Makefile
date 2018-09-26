CC=g++-8
CFLAGS=-Wall -std=c++17 -O3

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $@.cpp

run %: %
	./$@
