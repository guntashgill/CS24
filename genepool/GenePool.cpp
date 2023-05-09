#include "GenePool.h"

#include <fstream>
#include <sstream>
#include <vector>
// Helper function to split a string into fields.
std::vector<std::string> split(const std::string& str, char delimiter) {
  std::vector<std::string> fields;
  std::stringstream ss(str);
  std::string field;
  while (std::getline(ss, field, delimiter)) {
    fields.push_back(field);
  }
  return fields;
}

// Helper function to remove leading and trailing whitespaces from a string.
std::string trim(const std::string& str) {
  size_t first = str.find_first_not_of(" \t\n");
  if (std::string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(" \t\n");
  return str.substr(first, (last - first + 1));
}

// Constructor to build a database of people from a TSV file.
GenePool::GenePool(std::istream& stream) {
  std::string line;
  while (std::getline(stream, line)) {
    std::vector<std::string> fields = split(line, '\t');
    if (fields.size() < 3) {
      continue; // Invalid line format, skip it.
    }
    std::string name = trim(fields[0]);
    std::string father_name = trim(fields[1]);
    std::string mother_name = trim(fields[2]);

    // Check if the person already exists in the database.
    Person* person = find(name);
    if (person != nullptr) {
      // Person already exists, update their parents.
      if (!father_name.empty()) {
        Person* father = find(father_name);
        if (father == nullptr) {
          father = new Person(father_name);
          people_.insert(father);
        }
        person->is_parent(father);
      }
      if (!mother_name.empty()) {
        Person* mother = find(mother_name);
        if (mother == nullptr) {
          mother = new Person(mother_name);
          people_.insert(mother);
        }
        person->is_parent(mother);
      }
    } else {
      // Person doesn't exist, create a new one and add it to the database.
      person = new Person(name);
      people_.insert(person);
      if (!father_name.empty()) {
        Person* father = find(father_name);
        if (father == nullptr) {
          father = new Person(father_name);
          people_.insert(father);
        }
        person->is_parent(father);
      }
      if (!mother_name.empty()) {
        Person* mother = find(mother_name);
        if (mother == nullptr) {
          mother = new Person(mother_name);
          people_.insert(mother);
        }
        person->is_parent(mother);
      }
    }
  }
}

// Destructor to clean up the database.
GenePool::~GenePool() {
  for (auto person : people_) {
    delete person;
  }
}

// Return a set of all the people in the database.
std::set<Person*> GenePool::everyone() const {
  return people_;
}

// Find a person in the database by name.
// Return nullptr if there is no such person.
Person* GenePool::find(const std::string& name) const {
  for (auto person : people_) {
    if (person->name() == name) {
      return person;
    }
  }
  return nullptr;
}
