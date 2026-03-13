#ifndef SCHEDULING_DP_HPP
#define SCHEDULING_DP_HPP

#include "../core/algoritmo.h"
#include "InstanciaScheduling.hpp"
#include "SolucionSchedulling.hpp"

#include <vector>
#include <algorithm>

/**
 * @brief Programación Dinámica para resolver la planificación de UN día.
 *
 * Implementa la tabla:
 *
 * s[e][k] = max(
 *   s[e-1][k],
 *   s[e-1][k-1] + satisfaccion(e, turno)
 * )
 *
 * donde:
 *   e = empleados considerados
 *   k = slots de turno
 */
class SchedulingDP : public Algoritmo<InstanciaScheduling, SolucionScheduling> {

public:

  const char* name() const override {
    return "SchedulingDP";
  }

  SolucionScheduling ejecutar(const InstanciaScheduling& inst) const override {

    const int empleados = inst.getEmployees();
    const int turnos    = inst.getShifts();
    const int dia       = 0;   // instancia de 1 día

    /* ---------------------------------------
       Construir slots de turnos
    --------------------------------------- */

    std::vector<int> slots;

    for (int turno = 0; turno < turnos; ++turno) {
      int req = inst.getRequired(dia, turno);
      for (int i = 0; i < req; ++i)
        slots.push_back(turno);
    }

    const int K = slots.size();

    /* ---------------------------------------
       Tabla de programación dinámica
    --------------------------------------- */

    std::vector<std::vector<int>> dp(
        empleados + 1,
        std::vector<int>(K + 1, 0)
    );

    /* ---------------------------------------
       Rellenar DP
    --------------------------------------- */

    for (int e = 1; e <= empleados; ++e) {

      bool descansa = false;
      const auto& libres = inst.getFreeDays(e - 1);

      if (std::find(libres.begin(), libres.end(), dia) != libres.end())
        descansa = true;

      for (int k = 1; k <= K; ++k) {

        int turno = slots[k - 1];

        int sat = descansa
          ? 0
          : inst.getSatisfaction(e - 1, dia, turno);

        dp[e][k] = std::max(
            dp[e - 1][k],
            dp[e - 1][k - 1] + sat
        );
      }
    }

    /* ---------------------------------------
       Reconstrucción de la solución
    --------------------------------------- */

    SolucionScheduling sol(1, empleados);

    int e = empleados;
    int k = K;

    while (e > 0 && k > 0) {

      if (dp[e][k] == dp[e - 1][k]) {
        sol.set(0, e - 1, -1);
        e--;
      } else {

        int turno = slots[k - 1];
        sol.set(0, e - 1, turno);

        e--;
        k--;
      }
    }

    while (e > 0) {
      sol.set(0, e - 1, -1);
      e--;
    }

    sol.setScore(calcularScore(sol, inst));

    return sol;
  }

private:

  static int calcularScore(const SolucionScheduling& sol,
                           const InstanciaScheduling& inst) {

    const int dias      = inst.getDays();
    const int empleados = inst.getEmployees();
    const int turnos    = inst.getShifts();

    int sumaSat = 0;
    int turnosCubiertos = 0;

    for (int dia = 0; dia < dias; ++dia) {
      for (int turno = 0; turno < turnos; ++turno) {

        int asignados = 0;

        for (int emp = 0; emp < empleados; ++emp) {

          if (sol.get(dia, emp) == turno) {
            sumaSat += inst.getSatisfaction(emp, dia, turno);
            asignados++;
          }
        }

        if (asignados >= inst.getRequired(dia, turno))
          turnosCubiertos++;
      }
    }

    return sumaSat + 100 * turnosCubiertos;
  }
};

#endif
