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
** Archivo algoritmo.h: Base de un algoritmo
**/

#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "Instancia.h"
#include "Solucion.h"

/**
 * @brief Clase base de un algoritmo.
 *
 * @tparam Instancia Debe heredar de Instancia
 * @tparam Solucion Debe heredar de Solucion
 */
template <typename InstanciaType, typename SolucionType> class Algoritmo {
 public:
  virtual ~Algoritmo() = default;

  /**
   * @brief Ejecuta el algoritmo sobre una instancia.
   */
  virtual SolucionType ejecutar(const InstanciaType& instancia) = 0;

  /**
   * @brief Devuelve el name del algoritmo.
   */
  virtual const char* name() const = 0;
};

#endif
