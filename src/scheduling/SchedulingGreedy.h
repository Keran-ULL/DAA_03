#ifndef SCHEDULING_GREEDY_HPP
#define SCHEDULING_GREEDY_HPP

#include "../core/algoritmo.h"
#include "InstanciaScheduling.hpp"
#include "SolucionSchedulling.hpp"

#include <algorithm>

/**
 * @brief Algoritmo voraz para resolver el problema de planificación
 *        cuando la instancia tiene un único día.
 *
 * Para cada empleado:
 *  - Si el día está en freeDays → descanso (-1)
 *  - Si no → turno con mayor satisfacción
 */
class SchedulingGreedy :
public Algoritmo<InstanciaScheduling, SolucionScheduling> {

public:

  const char* name() const override {
    return "Greedy";
  }

  SolucionScheduling ejecutar(const InstanciaScheduling& inst) override {

    const int empleados = inst.getEmployees();
    const int turnos    = inst.getShifts();

    SolucionScheduling sol(1, empleados);

    for (int empleado = 0; empleado < empleados; ++empleado) {

      const auto& diasDescanso = inst.getFreeDays(empleado);

      bool descansa =
        std::find(diasDescanso.begin(),
                  diasDescanso.end(),
                  0) != diasDescanso.end();

      if (descansa) {
        sol.set(0, empleado, -1);
        continue;
      }

      int mejorTurno = 0;
      int mejorSat   = inst.getSatisfaction(empleado, 0, 0);

      for (int turno = 1; turno < turnos; ++turno) {

        int s = inst.getSatisfaction(empleado, 0, turno);

        if (s > mejorSat) {
          mejorSat = s;
          mejorTurno = turno;
        }
      }

      sol.set(0, empleado, mejorTurno);
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
