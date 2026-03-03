/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Practica 1/2: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo MedidorTiempos.h: Clase para medición de tiempos
**/

#ifndef MEDIDOR_TIEMPOS_H
#define MEDIDOR_TIEMPOS_H

#include "../exceptions.h"
#include <chrono>

class MedidorTiempos {
 public:

  template <typename Algoritmo, typename Instancia, typename Solucion>
  static double medir(Algoritmo& algoritmo, const Instancia& instancia) {
    try {
      auto inicio = std::chrono::high_resolution_clock::now();
      Solucion sol = algoritmo.ejecutar(instancia);
      auto fin = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double, std::milli> duracion = fin - inicio;
      return duracion.count();
    }
    catch (...) {
      throw TimeMeasurementException();
    }
  }
};

#endif
