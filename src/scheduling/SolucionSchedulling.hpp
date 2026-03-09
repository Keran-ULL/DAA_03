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
** Archivo SolucionScheduling.hpp: Implementación concreta de solucion para el problema Scheduling
**/

#ifndef SOLUCION_SCHEDULING_H
#define SOLUCION_SCHEDULING_H

#include "../core/Solucion.h"
#include <vector>
#include <iostream>

class SolucionScheduling : public Solucion {
 private:
  std::vector<std::vector<int>> plan_;
  int score_;

 public:
  SolucionScheduling(int days,int employees)
    : plan_(days,std::vector<int>(employees,-1)),
      score_(0) {}

  // getters
  int get(int dia,int empleado) const {return plan_[dia][empleado];}
  int score() const {return score_;}
  int getDays() const {return plan_.size();}
  int getEmployees() const {
    if (!plan_.empty()) return plan_[0].size();
    return 0;
  }

  // setters
  void setScore(int s) {score_=s;}
  void set(int dia,int empleado,int shift) {plan_[dia][empleado]=shift;}

  void mostrar(std::ostream& os) const override {
    os << "\nScore: " << score_ << "\n\n";
    int days = plan_.size();
    if (days == 0) return;
    int employees = plan_[0].size();

    int maxShift = -1;
    for (int d = 0; d < days; ++d)
      for (int e = 0; e < employees; ++e)
        if (plan_[d][e] > maxShift) maxShift = plan_[d][e];
    int shifts = (maxShift < 0) ? 1 : maxShift + 1;

    // Ancho de cada columna de día
    int colWidth = shifts * 3 + 1;

    // Ancho del prefijo Empleado N 
    int empDigits = (int)std::to_string(employees).size();
    int prefixWidth = 9 + empDigits + 1;  

    os << std::string(prefixWidth, ' ');
    for (int d = 0; d < days; ++d) {
      std::string label = "Dia " + std::to_string(d + 1);
      int len   = (int)label.size();
      int left  = (colWidth - len) / 2;
      int right = colWidth - len - left;
      os << std::string(left, ' ') << label << std::string(right, ' ');
    }
    os << "\n";

    for (int e = 0; e < employees; ++e) {
      std::string prefix = "Empleado " + std::to_string(e + 1) + " ";
      os << std::left << std::setw(prefixWidth) << prefix;
      for (int d = 0; d < days; ++d) {
        int turno = plan_[d][e];
        for (int s = 0; s < shifts; ++s)
          os << (turno == s ? "[X]" : "[ ]");
        os << " ";
      }
      os << "\n";
    }
    os << "\n";
  }
};

#endif