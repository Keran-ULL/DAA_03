#ifndef SCHEDULING_PARSER_HPP
#define SCHEDULING_PARSER_HPP

#include "InstanciaScheduling.hpp"
#include "../utils/json.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

class SchedulingParser {

public:

static InstanciaScheduling parse(const std::string& file){

  std::ifstream f(file);
  if(!f.is_open())
    throw std::runtime_error("Error abriendo archivo JSON");

  nlohmann::json j;
  f >> j;

  auto shifts = j["shifts"].get<std::vector<std::string>>();

  std::vector<std::string> employees;

  for(auto& e : j["employees"])
    employees.push_back(e["name"].get<std::string>());

  int days = j["planningHorizon"].get<int>();

  InstanciaScheduling instancia(shifts, employees, days);

  int id = 0;

  for(auto& e : j["employees"]){
    // freeDays puede ser un número o un array
    if (e["freeDays"].is_number()) {
        instancia.setFreeDays(id, e["freeDays"].get<int>());
    } else if (e["freeDays"].is_array()) {
        for (int d : e["freeDays"].get<std::vector<int>>()) {
            instancia.setFreeDays(id, d);
        }
    }
    id++;
  }

  for(auto& s : j["satisfaction"]){
    instancia.setSatisfaction(
      s["employee"].get<int>(),
      s["day"].get<int>(),
      s["shift"].get<int>(),
      s["value"].get<int>()
    );
  }

  for(auto& r : j["requiredEmployees"]){
    instancia.setRequired(
      r["day"].get<int>(),
      r["shift"].get<int>(),
      r["value"].get<int>()
    );
  }

  return instancia;
}

};

#endif