/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Práctica 3: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo MedidorTiempos.h: Clase para medición de tiempos
**/

#ifndef MEDIDOR_TIEMPOS_H
#define MEDIDOR_TIEMPOS_H

#include "../exceptions/exceptions.h"
#include <chrono>

class MedidorTiempos {
 public:

  /**
   * @brief Mide el tiempo de ejecución de un algoritmo sobre una instancia
   *
   * Este método ejecuta el algoritmo pasado como argumento sobre la
   * instancia proporcionada, y devuelve la duración en milisegundos.
   *
   * @tparam Algoritmo Tipo de la clase del algoritmo que implementa ejecutar()
   * @tparam Instancia Tipo de la instancia a resolver
   * @tparam Solucion Tipo de la solución devuelta por el algoritmo
   * @param algoritmo Algoritmo a ejecutar
   * @param instancia Instancia sobre la que ejecutar el algoritmo
   * @returns double Tiempo de ejecución en milisegundos
   * @throws TimeMeasurementException Si ocurre cualquier error durante la ejecución
   */
  template <typename Algoritmo, typename Instancia, typename Solucion> static double medir(Algoritmo& algoritmo, const Instancia& instancia) {
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
