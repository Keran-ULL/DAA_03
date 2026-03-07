/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Práctica 3: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 07/03/2026
**
** Archivo InstanciaScheduling.hpp: Implementación concreta de instancia para el problema Scheduling
**/

#ifndef INSTANCIA_SCHEDULING_H
#define INSTANCIA_SCHEDULING_H

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

  /**
   * @brief Constructor de la instancia
   * @param shifts Vector con los nombres de los turnos
   * @param employees Vector con los nombres de los empleados
   * @param days Número de días de planificación
   *
   * Inicializa las estructuras internas de satisfacción, requerimientos y días libres.
   */
  InstanciaScheduling( const std::vector<std::string>& shifts, 
                      const std::vector<std::string>& employees,
                      int days) : shifts_(shifts), employees_(employees), days_(days) {

    satisfaction_.resize( employees.size(), std::vector<std::vector<int>>(days, std::vector<int>(shifts.size(),0)));
    requiredEmployees_.resize(days, std::vector<int>(shifts.size(),0));
    freeDays_.resize(employees.size());
  }

  /**
   * @brief Devuelve el tamaño de la instancia (número de días)
   * @returns size_t Número de días
   */
  size_t size() const override {
    return days_;
  }

  /**
   * @brief Muestra información básica de la instancia
   * @param os Flujo de salida
   */
  void mostrar(std::ostream& os) const override {
    os << "Employees: " << employees_.size() << "\n";
    os << "Days: " << days_ << "\n";
    os << "Shifts: " << shifts_.size() << "\n";
  }

  // Getters
  int getDays() const { return days_; }
  int getEmployees() const { return employees_.size(); }
  int getShifts() const { return shifts_.size(); }
  int getSatisfaction(int empleado, int dia, int turno) const {return satisfaction_[empleado][dia][turno];}
  int getRequired(int dia,int turno) const {return requiredEmployees_[dia][turno];}
  const std::vector<std::string>& getShiftsVector() const { return shifts_; }
  const std::vector<std::string>& getEmployeesVector() const { return employees_; }
  const std::vector<int>& getFreeDays(int empleado) const {return freeDays_[empleado];}

  // Setters
  void setSatisfaction(int empleado, int dia, int turno, int valor) {satisfaction_[empleado][dia][turno]=valor;}
  void setRequired(int dia, int turno, int valor) {requiredEmployees_[dia][turno]=valor;}
  void setFreeDays(int e,int d) {freeDays_[e].push_back(d);}
};

#endif