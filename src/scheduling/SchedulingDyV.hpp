/**
 ** Universidad de La Laguna
 ** Escuela Superior de Ingeniería y Tecnología
 ** Grado en Ingeniería Informática
 ** Asignatura: Diseño y Análisis de Algoritmos
 ** Curso: 3º
 ** Práctica 3: Divide y Vencerás
 ** Autores: Marco Pérez Padilla, Keran Miranda González
 ** Fecha: 03/03/2026
 **
 ** Archivo SchedulingDyV.hpp: Algoritmo Divide y Vencerás para planificación.
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
 * @brief Algoritmo Divide y Vencerás para el problema de planificación.
 *
 * División: partir el horizonte de días por la mitad.
 *   - Los días de descanso de cada empleado (freeDays) son índices absolutos;
 *     se reparten según a qué mitad pertenecen y se reindexan localmente.
 *
 * Caso base (1 día):
 *   - Si el empleado tiene ese día marcado como descanso → -1.
 *   - Si no → turno de mayor satisfacción (greedy).
 *
 * Combinación:
 *   - Concatenar los planes de ambas mitades.
 *   - Recalcular el score con los datos de la instancia combinada.
 */
class SchedulingDyV
    : public DivideYVenceras<InstanciaScheduling, SolucionScheduling> {

 public:

  const char* name() const override { return "SchedulingDyV"; }

 protected:

  // ══════════════════════════════════════════════════════════════════════
  //  Caso base: 1 solo día
  // ══════════════════════════════════════════════════════════════════════

  bool isSmall(const InstanciaScheduling& inst) const override {
    return inst.getDays() == 1;
  }

  /**
   * @brief Resuelve greedy un único día (día local 0).
   *
   * Para cada empleado:
   *  - Si el día 0 está en su lista freeDays → descanso (-1).
   *  - Si no → turno con mayor satisfacción ese día.
   */
  SolucionScheduling solveSmall(
      const InstanciaScheduling& inst) const override {

    const int E = inst.getEmployees();
    const int T = inst.getShifts();

    SolucionScheduling sol(1, E);

    for (int e = 0; e < E; ++e) {

      // Comprobar si el empleado descansa el día local 0
      const auto& diasDescanso = inst.getFreeDays(e);
      bool descansa = std::find(diasDescanso.begin(),
                                diasDescanso.end(), 0)
                      != diasDescanso.end();

      if (descansa) {
        sol.set(0, e, -1);   // -1 = descanso
        continue;
      }

      // Greedy: turno de mayor satisfacción
      int mejorTurno = 0;
      int mejorSat   = inst.getSatisfaction(e, 0, 0);
      for (int t = 1; t < T; ++t) {
        int s = inst.getSatisfaction(e, 0, t);
        if (s > mejorSat) { mejorSat = s; mejorTurno = t; }
      }
      sol.set(0, e, mejorTurno);
    }

    // Score para 1 día
    sol.setScore(calcularScore(sol, inst));
    return sol;
  }

  // ══════════════════════════════════════════════════════════════════════
  //  División binaria por mitad de días
  // ══════════════════════════════════════════════════════════════════════

  /**
   * @brief Divide la instancia en [0, mitad) y [mitad, D).
   *
   * Copia los datos de satisfaction y requiredEmployees correspondientes
   * a cada mitad. Los días de descanso se filtran por mitad y se reindexan:
   *   - izquierda: días en [0, mitad)        → se conservan tal cual
   *   - derecha:   días en [mitad, D)        → se restan mitad (reindexado local)
   */
  std::pair<std::unique_ptr<InstanciaScheduling>,
            std::unique_ptr<InstanciaScheduling>>
  dividir(const InstanciaScheduling& inst) const override {

    const int E     = inst.getEmployees();
    const int D     = inst.getDays();
    const int T     = inst.getShifts();
    const int mitad = D / 2;
    const int resto = D - mitad;

    const auto& turnosVec    = inst.getShiftsVector();
    const auto& empleadosVec = inst.getEmployeesVector();

    // ── Crear sub-instancias (satisfaction y required inicializados a 0) ──
    auto izq = std::make_unique<InstanciaScheduling>(
        turnosVec, empleadosVec, mitad);
    auto der = std::make_unique<InstanciaScheduling>(
        turnosVec, empleadosVec, resto);

    // ── Copiar satisfaction ───────────────────────────────────────────────
    for (int e = 0; e < E; ++e) {
      for (int d = 0; d < mitad; ++d)
        for (int t = 0; t < T; ++t)
          izq->setSatisfaction(e, d, t, inst.getSatisfaction(e, d, t));

      for (int d = 0; d < resto; ++d)
        for (int t = 0; t < T; ++t)
          der->setSatisfaction(e, d, t,
              inst.getSatisfaction(e, mitad + d, t));
    }

    // ── Copiar requiredEmployees ──────────────────────────────────────────
    for (int d = 0; d < mitad; ++d)
      for (int t = 0; t < T; ++t)
        izq->setRequired(d, t, inst.getRequired(d, t));

    for (int d = 0; d < resto; ++d)
      for (int t = 0; t < T; ++t)
        der->setRequired(d, t, inst.getRequired(mitad + d, t));

    // ── Repartir días de descanso ─────────────────────────────────────────
    // freeDays_[e] contiene índices absolutos de días de descanso.
    // Los que caen en [0, mitad) van a izq sin cambio.
    // Los que caen en [mitad, D) van a der reindexados (día - mitad).
    for (int e = 0; e < E; ++e) {
      for (int diaDescanso : inst.getFreeDays(e)) {
        if (diaDescanso < mitad)
          izq->setFreeDays(e, diaDescanso);
        else
          der->setFreeDays(e, diaDescanso - mitad);
      }
    }

    return {std::move(izq), std::move(der)};
  }

  // ══════════════════════════════════════════════════════════════════════
  //  Combinación
  // ══════════════════════════════════════════════════════════════════════

  /**
   * @brief Concatena los planes de s1 y s2 y recalcula el score global.
   *
   * El score combinado se calcula sumando los scores individuales de cada
   * sub-solución, que ya fueron calculados correctamente sobre sus propias
   * sub-instancias. No se puede recalcular sobre la instancia original aquí
   * porque combinar solo recibe soluciones; la suma de scores parciales es
   * la aproximación correcta dentro del esquema D&V.
   */
  SolucionScheduling combinar(
      const SolucionScheduling& s1,
      const SolucionScheduling& s2) const override {

    const int D1 = s1.getDays();
    const int D2 = s2.getDays();
    const int E  = s1.getEmployees();

    SolucionScheduling res(D1 + D2, E);

    // Copiar s1
    for (int d = 0; d < D1; ++d)
      for (int e = 0; e < E; ++e)
        res.set(d, e, s1.get(d, e));

    // Copiar s2 (desplazado D1 días)
    for (int d = 0; d < D2; ++d)
      for (int e = 0; e < E; ++e)
        res.set(D1 + d, e, s2.get(d, e));

    // Score = suma de ambas sub-soluciones (calculados en sus sub-instancias)
    res.setScore(s1.score() + s2.score());

    return res;
  }

 private:

  // ══════════════════════════════════════════════════════════════════════
  //  Cálculo del score
  // ══════════════════════════════════════════════════════════════════════

  /**
   * @brief Calcula f(x) = Σ satisfaccion + Σ turnos_cubiertos * 100
   *
   * Un turno está cubierto si el número de empleados asignados a él ese día
   * es >= requiredEmployees[d][t].
   *
   * @param sol  Solución a evaluar.
   * @param inst Instancia de referencia (mismas dimensiones que sol).
   */
  static int calcularScore(const SolucionScheduling& sol,
                            const InstanciaScheduling& inst) {
    const int D = inst.getDays();
    const int E = inst.getEmployees();
    const int T = inst.getShifts();

    int sumaSat        = 0;
    int turnosCubiertos = 0;

    for (int d = 0; d < D; ++d) {
      for (int t = 0; t < T; ++t) {

        int asignados = 0;
        for (int e = 0; e < E; ++e) {
          if (sol.get(d, e) == t) {
            sumaSat += inst.getSatisfaction(e, d, t);
            ++asignados;
          }
        }

        if (asignados >= inst.getRequired(d, t))
          ++turnosCubiertos;
      }
    }

    return sumaSat + turnosCubiertos * 100;
  }
};

#endif // SCHEDULING_DYV_HPP