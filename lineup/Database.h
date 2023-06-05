#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <unordered_map>
#include "Report.h"

class Database {
private:
  std::unordered_map<unsigned int, const Report*> reports;
public:
  static Database* create();
public:
  Database();
  ~Database();

  void insert(const Report* report);
  std::vector<const Report*> search(float age, float height, float weight) const;
  void remove(unsigned int id);
};

#endif
