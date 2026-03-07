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
    os<<"Score: "<<score_<<"\n";
    for(size_t dia=0; dia < plan_.size(); dia++){
      os<<"Day "<<dia<<": ";
      for(size_t empleado=0; empleado < plan_[dia].size(); empleado++)
        os<<plan_[dia][empleado]<<" ";
      os<<"\n";
    }
  }
};

#endif