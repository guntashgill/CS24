#include "Person.h"

#include <algorithm>

// Helper function to check if a person is a parent of another person
bool isParentOf(Person* parent, Person* child) {
  return child->is_child(parent);
}

// Helper function to check if a person is a sibling of another person
bool isSiblingOf(Person* sibling1, Person* sibling2, SMod smod) {
  if (sibling1 == sibling2) {
    return false;
  }

  if (sibling1->mother() == sibling2->mother() && sibling1->father() == sibling2->father()) {
    return true;
  }

  if (smod == SMod::HALF && sibling1->mother() == sibling2->mother() && sibling1->father() != sibling2->father()) {
    return true;
  }

  if (smod == SMod::HALF && sibling1->mother() != sibling2->mother() && sibling1->father() == sibling2->father()) {
    return true;
  }

  return false;
}

// Constructor
Person::Person(const Person& other) {
  // Copy all member variables
  name_ = other.name_;
  gender_ = other.gender_;
  mother_ = other.mother_;
  father_ = other.father_;
  children_ = other.children_;
  birth_year_ = other.birth_year_;
}

// Copy assignment operator
Person& Person::operator=(const Person& other) {
  if (this == &other) {
    return *this;
  }

  // Copy all member variables
  name_ = other.name_;
  gender_ = other.gender_;
  mother_ = other.mother_;
  father_ = other.father_;
  children_ = other.children_;
  birth_year_ = other.birth_year_;

  return *this;
}

// Destructor
Person::~Person() {
  // Remove this person from the children set of their parents
  if (mother_ != nullptr) {
    mother_->children_.erase(this);
  }

  if (father_ != nullptr) {
    father_->children_.erase(this);
  }
}

// Required Getter Functions
const std::string& Person::name() const {
  return name_;
}

Gender Person::gender() const {
  return gender_;
}

Person* Person::mother() {
  return mother_;
}

Person* Person::father() {
  return father_;
}

int Person::birth_year() const {
  return birth_year_;
}


std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> ancestors;
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (this->mother != nullptr) {
            ancestors.insert(this->mother);
            for (auto& ancestor : this->mother->ancestors(PMod::ANY)) {
                ancestors.insert(ancestor);
            }
        }
    }

    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (this->father != nullptr) {
            ancestors.insert(this->father);
            for (auto& ancestor : this->father->ancestors(PMod::ANY)) {
                ancestors.insert(ancestor);
            }
        }
    }
  return ancestors;
}



std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> aunts;
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if (mother_ != nullptr) {
            std::set<Person*> maternal_siblings = mother_->siblings(pmod, smod);
            for (auto sibling : maternal_siblings) {
                if (sibling->gender() == Gender::FEMALE) {
                    aunts.insert(sibling);
                }
            }
        }
    }
    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if (father_ != nullptr) {
            std::set<Person*> paternal_siblings = father_->siblings(pmod, smod);
            for (auto sibling : paternal_siblings) {
                if (sibling->gender() == Gender::FEMALE) {
                    aunts.insert(sibling);
                }
            }
        }
    }
    return aunts;
}
std::set<Person*> brothers;
if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (this->mother != nullptr) {
        for (auto& child : this->mother->children()) {
            if (child->gender == Gender::MALE && child != this) {
                brothers.insert(child);
            }
        }
    }
  return brothers;
}
if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (this->father != nullptr) {
        for (auto& child : this->father->children()) {
            if (child->gender == Gender::MALE && child != this) {
                brothers.insert(child);
            }
        }
    }
  return brothers;
}

std::set<Person*> Person::children() {
  return this->children_;
}

// Returns a set of Person objects that are the cousins of this Person
std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
  std::set<Person*> cousins;
  std::set<Person*> uncles = this->uncles(pmod, smod);
  for (auto& uncle : uncles) {
    for (auto& cousin : uncle->children()) {
      if (cousin->gender == Gender::MALE && (smod == SMod::FULL || this->isHalfCousin(cousin) == (smod == SMod::HALF))) {
        cousins.insert(cousin);
      }
    }
  }
  std::set<Person*> aunts = this->aunts(pmod, smod);
  for (auto& aunt : aunts) {
    for (auto& cousin : aunt->children()) {
      if (cousin->gender == Gender::MALE && (smod == SMod::FULL || this->isHalfCousin(cousin) == (smod == SMod::HALF))) {
        cousins.insert(cousin);
      }
    }
  }
  return cousins;
}

// Returns a set of Person objects that are the daughters of this Person
std::set<Person*> Person::daughters() {
  std::set<Person*> daughters;
  for (auto& child : this->children()) {
    if (child->gender == Gender::FEMALE) {
      daughters.insert(child);
    }
  }
  return daughters;
}

// Returns a set of Person objects that are the descendants of this Person
std::set<Person*> Person::descendants() {
  std::set<Person*> descendants;
  for (auto& child : this->children_) {
    descendants.insert(child);
    auto grand_children = child->descendants();
    descendants.insert(grand_children.begin(), grand_children.end());
  }
  return descendants;
}

// Returns a set of Person objects that are the grandchildren of this Person
std::set<Person*> Person::grandchildren() {
  std::set<Person*> grandchildren;
  for (auto& child : this->children_) {
    auto grand_children = child->children();
    grandchildren.insert(grand_children.begin(), grand_children.end());
  }
  return grandchildren;
}

// Returns a set of Person objects that are the granddaughters of this Person
std::set<Person*> Person::granddaughters() {
  std::set<Person*> granddaughters;
  for (auto& grandchild : this->grandchildren()) {
    if (grandchild.getGender() == Gender::FEMALE) {
      granddaughters.insert(&grandchild);
    }
  }
  return granddaughters;
}

// Returns a set of Person objects that are the grandfathers of this Person
Person* person = new Person();
std::set<Person*> grandfathers = person->grandfathers(PMod::ANY);
if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (person->mother != nullptr) {
        if (person->mother->father != nullptr) {
            grandfathers.insert(person->mother->father);
        }
    }
}
if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (person->father != nullptr) {
        if (person->father->father != nullptr) {
            grandfathers.insert(person->father->father);
        }
    }
}

std::set<Person*> Person::grandmothers(PMod pmod) {
  std::set<Person*> grandmothers;
  if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (this->mother != nullptr) {
      grandmothers.insert(this->mother->mother);
    }
  }
  if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (this->father != nullptr) {
      grandmothers.insert(this->father->mother);
    }
  }
  return grandmothers;
}

std::set<Person*> Person::grandparents(PMod pmod) {
  std::set<Person*> grandparents = this->grandfathers(pmod);
  auto maternal_grandmothers = this->grandmothers(PMod::MATERNAL);
  grandparents.insert(maternal_grandmothers.begin(), maternal_grandmothers.end());
  auto paternal_grandmothers = this->grandmothers(PMod::PATERNAL);
  grandparents.insert(paternal_grandmothers.begin(), paternal_grandmothers.end());
  return grandparents;
}

std::set<Person*> Person::grandsons() {
  std::set<Person*> grandsons;
  for (auto& grandchild : this->grandchildren()) {
    if (grandchild->gender == Gender::MALE) {
      grandsons.insert(grandchild);
    }
  }
  return grandsons;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
  std::set<Person*> nephews;
  for (auto& sibling : this->siblings(pmod, smod)) {
    auto sibling_sons = sibling->sons();
    nephews.insert(sibling_sons.begin(), sibling_sons.end());
  }
  return nephews;
}

std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
  std::set<Person*> nieces;
  for (auto& sibling : this->siblings(pmod, smod)) {
    auto sibling_daughters = sibling->daughters();
    nieces.insert(sibling_daughters.begin(), sibling_daughters.end());
  }
  return nieces;
}

std::set<Person*> Person::parents(PMod pmod) {
  std::set<Person*> parents;
  if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (this->mother != nullptr) {
      parents.insert(this->mother);
    }
  }
  if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (this->father != nullptr) {
      parents.insert(this->father);
    }
  }
  return parents;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
  std::set<Person*> siblings;
  if (this->mother != nullptr) {
    auto maternal_siblings = this->mother->children(PMod::ANY, smod);
    siblings.insert(maternal_siblings.begin(), maternal_siblings.end());
  }
  if (this->father != nullptr) {
    auto paternal_siblings = this->father->children(PMod::ANY, smod);
    siblings.insert(paternal_siblings.begin(), paternal_siblings.end());
  }
  siblings.erase(this);
  return siblings;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
  std::set<Person*> sisters;
  for (auto& sibling : this->siblings(pmod, smod)) {
    if (sibling->gender == Gender::FEMALE) {
      sisters.insert(sibling);
    }
  }
  return sisters;
}

std::set<Person*> Person::sons() {
  std::set<Person*> sons;
  for (auto& child : this->children_) {
    if (child->gender == Gender::MALE) {
      sons.insert(child);
    }
  }
  return sons;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
  std::set<Person*> uncles;
  for (auto& sibling : this->siblings(pmod, smod)) {
    if (sibling->gender == Gender::MALE) {
      for (auto& child : sibling->children_) {
        if (child->gender == Gender::MALE && child != this) {
          uncles.insert(child);
        }
      }
    }
  }
  return uncles;
}



