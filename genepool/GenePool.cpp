#include "GenePool.h"

#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter) {
  std::vector<std::string> fields;
  std::stringstream ss(str);
  std::string field;
  while (std::getline(ss, field, delimiter)) {
    fields.push_back(field);
  }
  return fields;
}


std::string trim(const std::string& str) {
  size_t first = str.find_first_not_of(" \t\n");
  if (std::string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(" \t\n");
  return str.substr(first, (last - first + 1));
}

bool Person::is_parent(Person* other) const {
  return (father_ == other || mother_ == other);
}
GenePool::GenePool(std::istream& stream) {
  std::string line;
  while (std::getline(stream, line)) {
    std::vector<std::string> fields = split(line, '\t');
    if (fields.size() < 3) {
      continue;
    }
    std::string name = trim(fields[0]);
    std::string father_name = trim(fields[1]);
    std::string mother_name = trim(fields[2]);

    Person* person = find(name);
    if (person != nullptr) {
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

GenePool::~GenePool() {
  for (auto person : people_) {
    delete person;
  }
}

std::set<Person*> GenePool::everyone() const {
  return people_;
}

Person* GenePool::find(const std::string& name) const {
  for (auto person : people_) {
    if (person->name() == name) {
      return person;
    }
  }
  return nullptr;
}
