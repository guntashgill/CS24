CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: all clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

all: test

test: main.o Dictionary.o Helpers.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp Dictionary.h Errors.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Dictionary.o: Dictionary.cpp Dictionary.h Errors.h Helpers.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Helpers.o: Helpers.cpp Helpers.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f test main.o Dictionary.o Helpers.o

