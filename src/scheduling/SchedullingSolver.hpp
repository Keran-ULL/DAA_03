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
** Archivo SchedulingSolver.hpp: Implementación de un solver por backtracking
** para el problema Scheduling, calculando la asignación óptima de turnos
** según la satisfacción de los empleados.
**/

#ifndef SCHEDULING_SOLVER_HPP
#define SCHEDULING_SOLVER_HPP

#include "InstanciaScheduling.hpp"
#include "SolucionSchedulling.hpp"

/**
 * @brief Clase para resolver instancias de Scheduling mediante backtracking
 */
class SchedulingSolver {
 private:
  const InstanciaScheduling& instancia_; 
  SolucionScheduling best_;               

 public:
  /**
   * @brief Constructor del solver
   * @param instancia InstanciaScheduling a resolver
   */
  explicit SchedulingSolver(const InstanciaScheduling& instancia) : instancia_(instancia), best_(instancia.getDays(), instancia.getEmployees()) {}

  /**
   * @brief Ejecuta el solver y devuelve la mejor solución
   * @returns SolucionScheduling mejor solución encontrada
   */
  SolucionScheduling solve() {
    SolucionScheduling actual(instancia_.getDays(),instancia_.getEmployees());
    backtrack(0, 0, actual);
    return best_;
  }

 private:
  /**
   * @brief Función recursiva de backtracking que asigna turnos a empleados
   *        en cada día para explorar todas las combinaciones posibles y
   *        encontrar la asignación que maximice la satisfacción total.
   * @param dia Día actual
   * @param empleado Empleado actual
   * @param sol Solución parcial
   */
  void backtrack(int dia, int empleado, SolucionScheduling& sol) {
    if (dia == instancia_.getDays()) {
      evaluar(sol);
      return;
    }

    int next_dia = dia;
    int next_empleado = empleado + 1;
    if (next_empleado == instancia_.getEmployees()) {
      next_empleado = 0;
      next_dia++;
    }

    for (int turno = 0; turno < instancia_.getShifts(); turno++) {
      sol.set(dia, empleado, turno);
      backtrack(next_dia, next_empleado, sol);
    }
  }

  /**
   * @brief Evalúa la solución actual y actualiza la mejor solución si corresponde
   * @param sol Solución a evaluar
   */
  void evaluar(SolucionScheduling& sol) {
    int score = 0;

    for (int dia = 0; dia < instancia_.getDays(); dia++) {
      for (int empleado = 0; empleado < instancia_.getEmployees(); empleado++) {
        int turno = sol.get(dia, empleado);
        score += instancia_.getSatisfaction(empleado, dia, turno);
      }
    }

    if (score > best_.score()) {
      best_ = sol;
      best_.setScore(score);
    }
  }
};

#endif