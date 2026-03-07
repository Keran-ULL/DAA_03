#ifndef INSTANCIA_SCHEDULING_HPP
#define INSTANCIA_SCHEDULING_HPP

#include "../core/Instancia.h"
#include <vector>
#include <string>
#include <iostream>

class InstanciaScheduling : public Instancia {

private:

  std::vector<std::string> shifts_;
  std::vector<std::string> employees_;

  int days_;

  std::vector<std::vector<std::vector<int>>> satisfaction_;
  std::vector<std::vector<int>> requiredEmployees_;
  std::vector<std::vector<int>> freeDays_;

public:

  InstanciaScheduling(
      const std::vector<std::string>& shifts,
      const std::vector<std::string>& employees,
      int days)
      : shifts_(shifts),
        employees_(employees),
        days_(days) {

    satisfaction_.resize(
        employees.size(),
        std::vector<std::vector<int>>(days,
        std::vector<int>(shifts.size(),0)));

    requiredEmployees_.resize(days,
        std::vector<int>(shifts.size(),0));

    freeDays_.resize(employees.size());
  }

  size_t tamano() const override {
    return days_;
  }

  void mostrar(std::ostream& os) const override {

    os << "Employees: " << employees_.size() << "\n";
    os << "Days: " << days_ << "\n";
    os << "Shifts: " << shifts_.size() << "\n";
  }

  int getDays() const { return days_; }
  int getEmployees() const { return employees_.size(); }
  int getShifts() const { return shifts_.size(); }

  int getSatisfaction(int e,int d,int t) const {
    return satisfaction_[e][d][t];
  }

  int getRequired(int d,int t) const {
    return requiredEmployees_[d][t];
  }

  const std::vector<int>& getFreeDays(int e) const {
    return freeDays_[e];
  }

  void setSatisfaction(int e,int d,int t,int v){
    satisfaction_[e][d][t]=v;
  }

  void setRequired(int d,int t,int v){
    requiredEmployees_[d][t]=v;
  }

  void setFreeDays(int e,int d){
    freeDays_[e].push_back(d);
  }

  const std::vector<std::string>& getShiftsVector() const { return shifts_; }
  const std::vector<std::string>& getEmployeesVector() const { return employees_; }
};

#endif