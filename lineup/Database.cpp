
#include "Database.h"
#include "Errors.h"

Database* Database::create() {
  return new Database();
}

Database::Database() {}

Database::~Database() {
  for (const auto& pair : reports) {
    delete pair.second;
  }
  reports.clear();
}

void Database::insert(const Report* report) {
  if (reports.count(report->id) > 0) {
    throw DuplicateReport(report->id);
  }

  reports[report->id] = report;
}

std::vector<const Report*> Database::search(float age, float height, float weight) const {
  std::vector<const Report*> matchingReports;
  matchingReports.reserve(reports.size());

  for (const auto& pair : reports) {
    const Report* report = pair.second;
    if (age >= report->age.min && age <= report->age.max &&
        height >= report->height.min && height <= report->height.max &&
        weight >= report->weight.min && weight <= report->weight.max) {
      matchingReports.push_back(report);
    }
  }

  return matchingReports;
}

void Database::remove(unsigned int id) {
  auto it = reports.find(id);

  if (it != reports.end()) {
    const Report* report = it->second;
    reports.erase(it);
    delete report;
  } else {
    throw NoSuchReport(id);
  }
}