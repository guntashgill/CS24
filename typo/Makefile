CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

Typo: main.o Heap.o Wordlist.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp WordList.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Heap.o: Heap.cpp Heap.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Wordlist.o: Wordlist.cpp Wordlist.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f Typo main.o Heap.o Wordlist.o