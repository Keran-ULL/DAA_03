/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Practica 2: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 07/03/2026
**
** Archivo SchedulingParser.h: Parser de instancias Scheduling desde JSON
**/

#ifndef SCHEDULING_PARSER_H
#define SCHEDULING_PARSER_H

#include "InstanciaScheduling.hpp"
#include "../libreries/json.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * @brief Clase para parsear un archivo JSON y construir una instancia Scheduling
 */
class SchedulingParser {

 public:

  /**
   * @brief Parsea un archivo JSON para crear una instancia Scheduling
   * @param file Ruta del archivo JSON que contiene los datos de planificación
   * @returns InstanciaScheduling con turnos, empleados, días, satisfacciones y restricciones
   * @throws std::runtime_error si no se puede abrir el archivo
   */
  static InstanciaScheduling parse(const std::string& file) {
    std::ifstream f(file);
    if(!f.is_open())
      throw JSONParseException("No se pudo abrir el archivo: " + file);

    nlohmann::json j;
    f >> j;

    // Turnos
    auto shifts = j["shifts"].get<std::vector<std::string>>();

    std::vector<std::string> employees;
    for(auto& e : j["employees"])
      employees.push_back(e["name"].get<std::string>());

    // Horizon
    int days = j["planningHorizon"].get<int>();
    InstanciaScheduling instancia(shifts, employees, days);

    // Dias libres de empleados
    int empleado_id = 0;
    for(auto& e : j["employees"]){
      if (e["freeDays"].is_number()) {
        instancia.setFreeDays(empleado_id, e["freeDays"].get<int>());
      } else if (e["freeDays"].is_array()) {
        for (int dia : e["freeDays"].get<std::vector<int>>()) {
          instancia.setFreeDays(empleado_id, dia);
        }
      }
      empleado_id++;
    }

    // Satisfacciones
    for(auto& s : j["satisfaction"]){
      instancia.setSatisfaction(
        s["employee"].get<int>(),
        s["day"].get<int>(),
        s["shift"].get<int>(),
        s["value"].get<int>()
      );
    }

    // Empleados por dia
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