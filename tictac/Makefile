CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: all clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

all: game-check move

game-check: game-check.cpp move.o board.cpp
	${CXX} ${CXXFLAGS} -o $@ $+

move: move-check.o move.o
	${CXX} ${CXXFLAGS} -o $@ $+

move-check.o: Move-check.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $+

move.o: Move.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $+


clean:
	rm -f *.o move-check game-check move