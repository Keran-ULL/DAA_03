/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 3: Divide y Vencerás
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 07/03/2026
**
** Archivo SchedulingDyV.hpp: Algoritmo Divide y Vencerás para planificación
**/

#ifndef SCHEDULING_DYV_HPP
#define SCHEDULING_DYV_HPP

#include "../core/divideYvenceras.h"
#include "InstanciaScheduling.hpp"
#include "SolucionSchedulling.hpp"

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

/**
 * @brief Algoritmo Divide y Vencerás para el problema de planificación de turnos.
 *
 * División: partir el horizonte de días por la mitad.
 * Caso base: un único día → greedy (turno con mayor satisfacción si no es descanso).
 * Combinación: concatenar planes y sumar scores parciales.
 */
class SchedulingDyV : public DivideYVenceras<InstanciaScheduling, SolucionScheduling> {

  private:

    std::unique_ptr<
    Algoritmo<InstanciaScheduling, SolucionScheduling>
    > smallSolver_;

 public:
  /**
   * @brief Devuelve el nombre del algoritmo
   * @return const char* con el nombre
   */
  const char* name() const override { return "SchedulingDyV"; }

  SchedulingDyV(std::unique_ptr<Algoritmo<InstanciaScheduling,SolucionScheduling>> smallSolver) : smallSolver_(std::move(smallSolver)) {}


 protected:
  /**
   * @brief Determina si la instancia es lo suficientemente pequeña
   *        para resolverse de forma directa (1 día).
   * @param inst InstanciaScheduling a evaluar
   * @return true si es un solo día, false en caso contrario
   */
  bool isSmall(const InstanciaScheduling& inst) const override {
    return inst.getDays() == 1;
  }

  /**
   * @brief Resuelve el caso base de un único día de forma greedy.
   *
   * Para cada empleado:
   *  - Si el día 0 está en su lista de freeDays → descanso (-1)
   *  - Si no → turno con mayor satisfacción
   *
   * @param inst InstanciaScheduling de un día
   * @return SolucionScheduling con la asignación de turnos
   */
  SolucionScheduling solveSmall(const InstanciaScheduling& inst) const override {
    return smallSolver_->ejecutar(inst);
  }


  /**
   * @brief Divide la instancia en dos subproblemas por mitad de días.
   *
   * Días de descanso (freeDays) se reindexan para cada mitad.
   *
   * @param inst InstanciaScheduling a dividir
   * @return par de punteros únicos a InstanciaScheduling: izquierda y derecha
   */
  std::pair<std::unique_ptr<InstanciaScheduling>,
            std::unique_ptr<InstanciaScheduling>>
  dividir(const InstanciaScheduling& inst) const override {
    const int empleados = inst.getEmployees();
    const int dias      = inst.getDays();
    const int turnos    = inst.getShifts();
    const int mitad     = dias / 2;
    const int resto     = dias - mitad;

    const auto& turnosVec    = inst.getShiftsVector();
    const auto& empleadosVec = inst.getEmployeesVector();

    // sub-instancias
    auto izq = std::make_unique<InstanciaScheduling>(
        turnosVec, empleadosVec, mitad);
    auto der = std::make_unique<InstanciaScheduling>(
        turnosVec, empleadosVec, resto);

    // Satisfaccion
    for (int empleado = 0; empleado < empleados; ++empleado) {
      for (int dia = 0; dia < mitad; ++dia)
        for (int turno = 0; turno < turnos; ++turno)
          izq->setSatisfaction(empleado, dia, turno,
                               inst.getSatisfaction(empleado, dia, turno));

      for (int dia = 0; dia < resto; ++dia)
        for (int turno = 0; turno < turnos; ++turno)
          der->setSatisfaction(empleado, dia, turno,
              inst.getSatisfaction(empleado, mitad + dia, turno));
    }

    // requiredEmployees
    for (int dia = 0; dia < mitad; ++dia)
      for (int turno = 0; turno < turnos; ++turno)
        izq->setRequired(dia, turno, inst.getRequired(dia, turno));

    for (int dia = 0; dia < resto; ++dia)
      for (int turno = 0; turno < turnos; ++turno)
        der->setRequired(dia, turno, inst.getRequired(mitad + dia, turno));

    // días de descanso
    for (int empleado = 0; empleado < empleados; ++empleado) {
      for (int diaDescanso : inst.getFreeDays(empleado)) {
        if (diaDescanso < mitad)
          izq->setFreeDays(empleado, diaDescanso);
        else
          der->setFreeDays(empleado, diaDescanso - mitad);
      }
    }

    return {std::move(izq), std::move(der)};
  }

  /**
   * @brief Combina dos sub-soluciones en una solución completa.
   *
   * Concatena planes de s1 y s2 y suma los scores parciales.
   *
   * @param s1 Solución izquierda
   * @param s2 Solución derecha
   * @return SolucionScheduling combinada
   */
  SolucionScheduling combinar(const SolucionScheduling& s1, const SolucionScheduling& s2) const override {
    const int D1 = s1.getDays();
    const int D2 = s2.getDays();
    const int E  = s1.getEmployees();

    SolucionScheduling res(D1 + D2, E);
    // s1
    for (int dia = 0; dia < D1; ++dia)
      for (int empleado = 0; empleado < E; ++empleado)
        res.set(dia, empleado, s1.get(dia, empleado));

    // s2 con desplazamiento de días
    for (int dia = 0; dia < D2; ++dia)
      for (int empleado = 0; empleado < E; ++empleado)
        res.set(D1 + dia, empleado, s2.get(dia, empleado));

    // Score total = suma de scores parciales
    res.setScore(s1.score() + s2.score());

    return res;
  }

 private:

  /**
   * @brief Calcula el score de una solución.
   *
   * Score = suma de satisfacciones + 100 * número de turnos cubiertos
   *
   * @param sol SoluciónScheduling a evaluar
   * @param inst InstanciaScheduling de referencia
   * @return entero con el score calculado
   */
  static int calcularScore(const SolucionScheduling& sol, const InstanciaScheduling& inst) {
    const int dias     = inst.getDays();
    const int empleados = inst.getEmployees();
    const int turnos   = inst.getShifts();

    int sumaSat        = 0;
    int turnosCubiertos = 0;
    for (int dia = 0; dia < dias; ++dia) {
      for (int turno = 0; turno < turnos; ++turno) {
        int asignados = 0;
        for (int empleado = 0; empleado < empleados; ++empleado) {
          if (sol.get(dia, empleado) == turno) {
            sumaSat += inst.getSatisfaction(empleado, dia, turno);
            ++asignados;
          }
        }
        if (asignados >= inst.getRequired(dia, turno))
          ++turnosCubiertos;
      }
    }
    return sumaSat + turnosCubiertos * 100;
  }
};

#endif 