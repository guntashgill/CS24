#include "GenePool.h"

void Person::is_child(Person* child) {
  children_.insert(child);
}

void Person::is_sibling(Person* sibling) {
  siblings_.insert(sibling);
}
GenePool::GenePool(std::istream& stream) {
  std::string line;
  while (std::getline(stream, line)) {
    if (line.empty() || (line[0] == '#')){
      continue;
    }
    std::istringstream lineStream(line);
    std::string name = "";
    Gender gender = Gender::ANY;
    Person* mother = nullptr;
    Person* father = nullptr;

    const size_t NUM_FIELDS = 4;
    for (size_t i = 0; i < NUM_FIELDS; ++i){
      std::string field;
      std::getline(lineStream, field, '\t');
      if (i == 0){
        name = field;
      }
      else if (i ==1){
        if (field == "male"){
          gender = Gender::MALE;
        }
        else {
          gender = Gender::FEMALE;
        }
      }
      else if (i==2){
        if (field != "???"){
          Person* tempPerson = nullptr;
          if (find(field) != nullptr){
            tempPerson = find(field);
          }
          if (tempPerson != nullptr ){
            mother = tempPerson;
          }
        }
      }
      else {
        if (field != "???") {
          Person* tempPerson = nullptr;
          if (find(field) != nullptr){
            tempPerson = find(field);
          }
          if (tempPerson != nullptr){
            father = tempPerson;
          }
        }
      }
    }
    Person* newPerson = new Person(name, gender, mother, father);
    peopleSet.insert(newPerson);
  }
  is_children();
  is_sib();
}

GenePool::~GenePool() {
  for (Person* person : peopleSet){
    delete person;
  }
}

std::set<Person*> GenePool::everyone() const{
  return peopleSet;
}

Person* GenePool:: find(const std::string& name) const{
  for (Person* person : peopleSet){
    if (person->name() == name) {
      return person;
    }
  }
  return nullptr;
}

void GenePool::is_children() {
  for(Person* person : peopleSet) {
    if (person->mother() != nullptr) {
      person->mother()->is_child(person);
    }
    if (person->father() != nullptr){
      person->father()->is_child(person);
    }
  }
}

void GenePool::is_sib() {
  for (Person* person : peopleSet){
    if (person->mother() != nullptr) {
      for (Person* child : person->mother()->children()) {
        if (child != person) {
          person->is_sibling(child);
        }
      }
    }
    if (person->father() != nullptr) {
      for (Person* child : person->father()->children()) {
        if (child != person) {
          person->is_sibling(child);
        }
      }
    }
  }
}


