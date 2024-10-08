#include "Person.h"

#include <algorithm>



bool isSiblingOf(Person* sibling1, Person* sibling2, SMod smod = SMod::ANY) {
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

Person::Person(const std::string& name, Gender gender, Person* mother, Person* father){
    name_ = name;
    gender_ = gender;
    mother_ = mother; 
    father_ = father;
};


Person::Person(const Person& other) {
    name_ = other.name_;
    gender_ = other.gender_;
    mother_ = other.mother_;
    father_ = other.father_;
    children_ = other.children_;
}

Person& Person::operator=(const Person& other) {
    if (this == &other) {
        return *this;
    }

    name_ = other.name_;
    gender_ = other.gender_;
    mother_ = other.mother_;
    father_ = other.father_;
    children_ = other.children_;

    return *this;
}

Person::~Person() {
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


std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> ancestors;
    
    if (pmod == PMod::ANY || pmod == PMod::MATERNAL) {
        if (mother_) {
            ancestors.insert(mother_);
            std::set<Person*> maternal_ancestors = mother_->ancestors(PMod::MATERNAL);
            ancestors.insert(maternal_ancestors.begin(), maternal_ancestors.end());
            std::set<Person*> maternal_ancestors_all = mother_->ancestors(PMod::ANY);
            ancestors.insert(maternal_ancestors_all.begin(), maternal_ancestors_all.end());
        }
    }
    
    if (pmod == PMod::ANY || pmod == PMod::PATERNAL) {
        if (father_) {
            ancestors.insert(father_);
            std::set<Person*> paternal_ancestors = father_->ancestors(PMod::PATERNAL);
            ancestors.insert(paternal_ancestors.begin(), paternal_ancestors.end());
            std::set<Person*> paternal_ancestors_all = father_->ancestors(PMod::ANY);
            ancestors.insert(paternal_ancestors_all.begin(), paternal_ancestors_all.end());
        }
    }
    
    return ancestors;
}





std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> aunts;
    if (pmod != PMod::MATERNAL) {
        if (father_) {
            for (auto sibling: father_->sisters(PMod::ANY, smod)){
                aunts.insert(sibling);
            }
        }
    }
    if (pmod != PMod::PATERNAL) {
        if (mother_) {
            for (auto sibling: mother_->sisters(PMod::ANY, smod)){
                aunts.insert(sibling);
            }
        }
    }
    return aunts;
}



std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> brothers;
    for(auto sibling : siblings(pmod, smod)){
        if (sibling ->gender_ == Gender::MALE){
            brothers.insert(sibling);
        }
    }
    return brothers;
}





std::set<Person*> Person::children() {
    return this->children_;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> cousins;

    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && (smod == SMod::FULL || smod == SMod::ANY)) {
        if (mother_) {
            std::set<Person*> maternal_siblings = mother_->siblings(PMod::ANY, SMod::FULL);

            for (auto sibling : maternal_siblings) {
                std::set<Person*> children = sibling->children();
                cousins.insert(children.begin(), children.end());
            }
        }
    }

    if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && (smod == SMod::HALF || smod == SMod::ANY)) {
        if (mother_) {
            std::set<Person*> maternal_half_siblings = mother_->siblings(PMod::ANY, SMod::HALF);

            for (auto sibling : maternal_half_siblings) {
                std::set<Person*> children = sibling->children();
                cousins.insert(children.begin(), children.end());
            }
        }
    }

    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && (smod == SMod::FULL || smod == SMod::ANY)) {
        if (father_) {
            std::set<Person*> paternal_siblings = father_->siblings(PMod::ANY, SMod::FULL);

            for (auto sibling : paternal_siblings) {
                std::set<Person*> children = sibling->children();
                cousins.insert(children.begin(), children.end());
            }
        }
    }

    if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && (smod == SMod::HALF || smod == SMod::ANY)) {
        if (father_) {
            std::set<Person*> paternal_half_siblings = father_->siblings(PMod::ANY, SMod::HALF);

            for (auto sibling : paternal_half_siblings) {
                std::set<Person*> children = sibling->children();
                cousins.insert(children.begin(), children.end());
            }
        }
    }

    cousins.erase(this);
    return cousins;
}



std::set<Person*> Person::daughters() {
    std::set<Person*> result;
    for (auto child : children_) {
        if (child->gender() == Gender::FEMALE) {
            result.insert(child);
        }
    }
    return result;
}


std::set<Person*> Person::descendants() {
    std::set<Person*> descendants;
    for (auto& child : this->children_) {
        descendants.insert(child);
        auto grand_children = child->descendants();
        descendants.insert(grand_children.begin(), grand_children.end());
    }
    return descendants;
}

std::set<Person*> Person::grandchildren() {
    std::set<Person*> grandchildren;
    for (auto& child : this->children_) {
        auto grand_children = child->children();
        grandchildren.insert(grand_children.begin(), grand_children.end());
    }
    return grandchildren;
}

std::set<Person*> Person::granddaughters() {
    std::set<Person*> granddaughters;

    std::set<Person*> children = this->children();

    for (auto child : children) {
        std::set<Person*> granddaughtersOfChild = child->daughters();
        for (auto granddaughter : granddaughtersOfChild) {
            granddaughters.insert(granddaughter);
        }
    }

    return granddaughters;
}


std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> result;

    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        auto maternal_parents = parents(PMod::MATERNAL);
        for (auto parent : maternal_parents) {
            auto maternal_grandfathers = parent->parents(PMod::PATERNAL);
            for (auto grandfather : maternal_grandfathers) {
                if (grandfather && grandfather->gender() == Gender::MALE) {
                    result.insert(grandfather);
                }
            }
        }
    }

    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        auto paternal_parents = parents(PMod::PATERNAL);
        for (auto parent : paternal_parents) {
            auto paternal_grandfathers = parent->parents(PMod::PATERNAL);
            for (auto grandfather : paternal_grandfathers) {
                if (grandfather && grandfather->gender() == Gender::MALE) {
                    result.insert(grandfather);
                }
            }
        }
    }

    return result;
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;
    if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        auto maternal_parents = parents(PMod::MATERNAL);
        for (auto parent : maternal_parents) {
            auto maternal_grandmothers = parent->parents(PMod::MATERNAL);
            for (auto grandmother : maternal_grandmothers) {
                if (grandmother && grandmother->gender() == Gender::FEMALE) {
                    result.insert(grandmother);
                }
            }
        }
    }

    if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        auto paternal_parents = parents(PMod::PATERNAL);
        for (auto parent : paternal_parents) {
            auto paternal_grandmothers = parent->parents(PMod::MATERNAL);
            for (auto grandmother : paternal_grandmothers) {
                if (grandmother && grandmother->gender() == Gender::FEMALE) {
                    result.insert(grandmother);
                }
            }
        }
    }

    return result;
}


std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> result;
    auto grandfathersSet = grandfathers(pmod);
    result.insert(grandfathersSet.begin(), grandfathersSet.end());
    auto grandmothersSet = grandmothers(pmod);
    result.insert(grandmothersSet.begin(), grandmothersSet.end());

    return result;
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
    if (pmod != PMod::MATERNAL) {
        for (auto sibling : siblings_) {
            if (smod != SMod::HALF){
                if (father_ && sibling -> father_ && sibling -> mother_){
                    if ((sibling -> father_ == father_) && (sibling -> mother_ == mother_)) {
                        result.insert(sibling);
                    }
                }
            }
            if (smod != SMod::FULL) {
                if(father_ && sibling-> father_){
                    if ((sibling -> father_== father_)&& (!sibling -> mother_ || sibling -> mother_!= mother_)){
                        result.insert(sibling);
                    }
                }
            }
        }
    }
    if (pmod != PMod::PATERNAL) {
        for (auto sibling : siblings_) {
            if (smod != SMod::HALF){
                if (mother_ && sibling -> mother_ && sibling -> father_){
                    if ((sibling -> mother_ == mother_) && (sibling -> father_ == father_)) {
                        result.insert(sibling);
                    }
                }
            }
            if (smod != SMod::FULL) {
                if(mother_ && sibling-> mother_){
                    if ((sibling -> mother_ == mother_)&& (!sibling -> father_ || sibling -> father_ != father_)){
                        result.insert(sibling);
                    }
                }
            }
        }
    }
    return result;

}
std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    std::set<Person*> sisters;

    if (mother_ && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) {
        for (auto child : mother_->children_) {
            if (child != this && child->gender_ == Gender::FEMALE) {
                if (smod == SMod::ANY || (smod == SMod::FULL && child->mother_ == mother_ && child->father_ == father_) || (smod == SMod::HALF && child->mother_ == mother_ && child->father_ != father_)) {
                    sisters.insert(child);
                }
            }
        }
    }
    if (father_ && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) {
        for (auto child : father_->children_) {
            if (child != this && child->gender_ == Gender::FEMALE) {
                if (smod == SMod::ANY || (smod == SMod::FULL && child->mother_ == mother_ && child->father_ == father_) || (smod == SMod::HALF && child->father_ == father_ && child->mother_ != mother_)) {
                    sisters.insert(child);
                }
            }
        }
    }

    return sisters;
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
    std::set<Person*> uncles;
    
    if (pmod != PMod::MATERNAL) {
        if (father_) {
            for (auto sibling : father_->brothers(PMod::ANY, smod)) {
                uncles.insert(sibling);
            }
        }
    }
    
    if (pmod != PMod::PATERNAL) {
        if (mother_) {
            for (auto sibling : mother_->brothers(PMod::ANY, smod)) {
                uncles.insert(sibling);
            }
        }
    }
    
    return uncles;
}







