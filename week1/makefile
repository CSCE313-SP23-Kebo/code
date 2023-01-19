all: buggy

buggy: buggy.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -fsanitize=address,undefined -o buggy buggy.cpp

clean:
	rm buggy
