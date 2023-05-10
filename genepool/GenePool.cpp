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
void Person::is_child(Person* child) {
  children_.insert(child);
}

void Person::is_sibling(Person* sibling) {
  siblings_.insert(sibling);
}

GenePool::GenePool(std::istream& stream) {
  std::string line;
  while (std::getline(stream, line)) {
    std::vector<std::string> fields = split(line, '\t');
    if (fields.size() < 3) {
      continue;
    }
    std::string name = trim(fields[0]);
    std::string gender = trim(fields[1]);
    std::string father_name = trim(fields[2]);
    std::string mother_name = trim(fields[3]);

    Gender GenderEnum;
    if (gender == "female"){
      GenderEnum = Gender::FEMALE;
    }
    else {
      GenderEnum = Gender::MALE;
    }

    Person* fatherPointer = find(father_name);
    Person* motherPointer = find(mother_name);

    Person* newPerson = new Person(name, GenderEnum, motherPointer, fatherPointer);
    peopleByName[name] = newPerson; 
  }
}
    

GenePool::~GenePool() {
  for (auto person : peopleByName) {
    delete person.second;
  }
}

std::set<Person*> GenePool::everyone() const{
  std::set<Person*> setPerson;
  for(auto somePerson : peopleByName){
    setPerson.insert(somePerson.second);
  }
  return setPerson; 
}

Person* GenePool::find(const std::string& name) const{
  for (auto person : peopleByName) {
    if (person.first == name) {
      return person.second;
    }
  }
  return nullptr;
}

void GenePool::setChildren() {
  for(Person* person : people) {
    if (person->mother() != nullptr) {
      person->mother()->is_child(person);
    }
    if (person->father()!= nullptr){
      person->father()->is_child(person);
    }
  }
}

void GenePool::setSiblings() {
  for (Person* person : people) {
    if (person->mother() != nullptr) {
      for (Person* child : person->mother()->children()) {
        if (child != person) {
          person->is_sibling(child);
        }
      }
    }
  }
}
   

