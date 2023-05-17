CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

Counter: main.o Counter.o Iterator.o word-count.o
	${CXX} $(CXXFLAGS) -o $@ $+


main.o: main.cpp Counter.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Counter.o: Counter.cpp Counter.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Iterator.o: Iterator.cpp Counter.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

word-count.o: word-count.cpp Counter.h
	${CXX} $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f Counter main.o Counter.o Iterator.o word-count.o