#ifndef GENEOOL_H
#define GENEOOL_H

#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include "Person.h"

class GenePool {
public:
GenePool(std::istream& stream);
~GenePool();
std::set<Person*> everyone() const;
Person* find(const std::string& name) const;
void is_children();
void is_sib();

private:
std::set<Person*> peopleSet;
};

#endif 