CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

all: main.o Database.o
	${CXX} $(CXXFLAGS) -o $@ $+


main.o: main.cpp Database.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Database.o: Database.cpp Database.h Report.h Errors.h
	${CXX} $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f all main.o Database.o