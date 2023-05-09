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
    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mother_) {
            ancestors.insert(mother_);
            std::set<Person*> maternal_ancestors = mother_->ancestors(PMod::MATERNAL);
            ancestors.insert(maternal_ancestors.begin(), maternal_ancestors.end());
        }
    }
    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (father_) {
            ancestors.insert(father_);
            std::set<Person*> paternal_ancestors = father_->ancestors(PMod::PATERNAL);
            ancestors.insert(paternal_ancestors.begin(), paternal_ancestors.end());
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
std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> brothers;
    if (mother_ && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) {
        for (auto child : mother_->children_) {
            if (child != this && child->gender_ == Gender::MALE && (smod == SMod::ANY || (smod == SMod::FULL && child->mother_ == mother_ && child->father_ == father_) || (smod == SMod::HALF && (child->mother_ == mother_ || child->father_ == father_)))) {
                brothers.insert(child);
            }
        }
    }
    if (father_ && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) {
        for (auto child : father_->children_) {
            if (child != this && child->gender_ == Gender::MALE && (smod == SMod::ANY || (smod == SMod::FULL && child->mother_ == mother_ && child->father_ == father_) || (smod == SMod::HALF && (child->mother_ == mother_ || child->father_ == father_)))) {
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
  std::set<Person*> aunts_uncles = aunts(pmod, smod);
  for (auto aunt_uncle : aunts_uncles) {
    std::set<Person*> children = aunt_uncle->children();
    for (auto child : children) {
      std::set<Person*> child_siblings = child->siblings(pmod, smod);
      cousins.insert(child_siblings.begin(), child_siblings.end());
    }
  }
  cousins.erase(this);
  return cousins;
}


// Returns a set of Person objects that are the daughters of this Person
std::set<Person*> Person::daughters() {
  std::set<Person*> result;
  for (auto child : children_) {
    if (child->gender() == Gender::FEMALE) {
      result.insert(child);
    }
  }
  return result;
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

  // Get all children of this person
  std::set<Person*> children = this->children();

  // Iterate over each child
  for (auto child : children) {
    // Get all female grandchildren of the child
    std::set<Person*> granddaughtersOfChild = child->daughters();
    for (auto granddaughter : granddaughtersOfChild) {
      // Add the granddaughter to the set of all granddaughters
      granddaughters.insert(granddaughter);
    }
  }

  return granddaughters;
}


std::set<Person*> Person::grandfathers(PMod pmod) {
  std::set<Person*> grandfathers;

  std::set<Person*> ancestors_set = ancestors(pmod);

  for (auto it = ancestors_set.begin(); it != ancestors_set.end(); ++it) {
    Person* ancestor = *it;
    if (ancestor->gender() == Gender::MALE) {
      Person* father = ancestor->father();
      if (father != nullptr && father->gender() == Gender::MALE) {
        grandfathers.insert(father);
      }
    }
  }

  return grandfathers;
}


std::set<Person*> Person::grandmothers(PMod pmod) {
  std::set<Person*> result;
  std::set<Person*> grandparents = ancestors(pmod);
  for (Person* grandparent : grandparents) {
    if (grandparent->gender() == Gender::FEMALE) {
      result.insert(grandparent);
    }
  }
  return result;
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
  for (auto child : children_) {
    for (auto grandchild : child->children_) {
      if (grandchild->gender() == Gender::MALE) {
        grandsons.insert(grandchild);
      }
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
  std::set<Person*> result;
  
  if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (mother_) {
      result.insert(mother_);
    }
  }
  
  if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (father_) {
      result.insert(father_);
    }
  }
  
  return result;
}


std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
  std::set<Person*> result;
  if (mother_ && father_) {
    for (auto child : mother_->children_) {
      if (child != this && child->gender_ == Gender::FEMALE && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) {
        if (smod == SMod::ANY || (smod == SMod::FULL && child->father_ == father_) || (smod == SMod::HALF && child->father_ != father_)) {
          result.insert(child);
        }
      }
    }
    for (auto child : father_->children_) {
      if (child != this && child->gender_ == Gender::MALE && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) {
        if (smod == SMod::ANY || (smod == SMod::FULL && child->mother_ == mother_) || (smod == SMod::HALF && child->mother_ != mother_)) {
          result.insert(child);
        }
      }
    }
  }
  return result;
}


std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
  std::set<Person*> result;
  if (mother_) {
    for (auto child : mother_->children_) {
      if (child != this && child->gender_ == Gender::FEMALE) {
        if (smod == SMod::ANY || is_sibling(child, smod)) {
          if (pmod == PMod::ANY || child->is_ancestor(this, pmod)) {
            result.insert(child);
          }
        }
      }
    }
  }
  return result;
}

std::set<Person*> Person::sons() {
  std::set<Person*> result;
  for (auto child : children_) {
    if (child->gender_ == Gender::MALE) {
      result.insert(child);
    }
  }
  return result;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
  std::set<Person*> result;
  if (mother_) {
    for (auto sibling : mother_->siblings(pmod, smod)) {
      if (sibling->gender_ == Gender::MALE) {
        result.insert(sibling);
      }
    }
  }
  if (father_) {
    for (auto sibling : father_->siblings(pmod, smod)) {
      if (sibling->gender_ == Gender::MALE) {
        result.insert(sibling);
      }
    }
  }
  return result;
}




