#ifndef PERSON_H
#define PERSON_H

#include "Enums.h"

#include <set>
#include <string>

// This is the Person class you need to implement.
// It has many member functions that perform relationship queries.
// Add any member variables you need to support this.
// Implement the member functions in Person.cpp.

class Person {
private:
  std::string name_;
  Gender gender_;
  Person* mother_;
  Person* father_;
  std::set<Person*> children_;
  std::set<Person*> siblings_;

public:
  // Constructor
  Person(const std::string& name) : name_(name), mother_(nullptr), father_(nullptr) {}
  Person(const std::string& name, Gender gender, Person* mother, Person* father);
  
  // Copy Constructor
  Person(const Person& other);
  
  // Copy Assignment Operator
  Person& operator=(const Person& other);
  
  // Destructor
  ~Person();


  // Required Getter Functions
  const std::string& name() const;
  Gender gender() const;
  Person* mother();
  Person* father();
  const std::set<Person*> sibling();

  // Required Relationship Functions
  std::set<Person*> ancestors(PMod pmod = PMod::ANY);
  std::set<Person*> aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> children();
  std::set<Person*> cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> daughters();
  std::set<Person*> descendants();
  std::set<Person*> grandchildren();
  std::set<Person*> granddaughters();
  std::set<Person*> grandfathers(PMod pmod = PMod::ANY);
  std::set<Person*> grandmothers(PMod pmod = PMod::ANY);
  std::set<Person*> grandparents(PMod pmod = PMod::ANY);
  std::set<Person*> grandsons();
  std::set<Person*> nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> parents(PMod pmod = PMod::ANY);
  std::set<Person*> siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> sons();
  std::set<Person*> uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  

  // Other Member Functions
  void is_child(Person* children);
  void is_sibling(Person* sibling);
  

};


#endif



