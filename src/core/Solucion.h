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
** Archivo solucion.h: Representación de soluciones para problemas
**/

#ifndef SOLUCION_H
#define SOLUCION_H

#include <iostream>

/**
 * @brief Clase base abstracta que representa
 *        la solución de un problema.
 *
 * Separada de Instancia para cumplir SRP.
 */
class Solucion {
 public:
  virtual ~Solucion() = default;

  /**
   * @brief Muestra la solución por pantalla.
   */
  virtual void mostrar(std::ostream& os) const = 0;
};

#endif
