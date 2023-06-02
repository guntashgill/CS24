#include "Database.h"
#include "Errors.h"

Database* Database::create() {
  return new Database();
}

Database::Database() {}

Database::~Database() {
  // Clean up remaining reports in the database
  for (const Report* report : reports) {
    delete report;
  }
}

void Database::insert(const Report* report) {
  // Check if a report with the same ID already exists
  for (const Report* existingReport : reports) {
    if (existingReport->id == report->id) {
      throw DuplicateReport(report->id);
    }
  }

  reports.push_back(report);
}

std::vector<const Report*> Database::search(float age, float height, float weight) const {
  std::vector<const Report*> matchingReports;

  for (const Report* report : reports) {
    // Check if the suspect's attributes fall within the ranges listed on the report
    if (age >= report->age.min && age <= report->age.max &&
        height >= report->height.min && height <= report->height.max &&
        weight >= report->weight.min && weight <= report->weight.max) {
      matchingReports.push_back(report);
    }
  }

  return matchingReports;
}

void Database::remove(unsigned int id) {
  bool reportFound = false;

  for (auto it = reports.begin(); it != reports.end(); ++it) {
    const Report* report = *it;

    if (report->id == id) {
      reports.erase(it);
      delete report;
      reportFound = true;
      break;
    }
  }

  if (!reportFound) {
    throw NoSuchReport(id);
  }
}