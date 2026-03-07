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
** Archivo SolucionVector.h: Implementación concreta de solucion basada en vector
**/

#ifndef SOLUCION_VECTOR_HPP
#define SOLUCION_VECTOR_HPP

#include "../core/Solucion.h"
#include <vector>
#include <iostream>

/**
 * @brief Representa la solución de un problema de ordenación.
 * 
 * Almacena un vector ordenado.
 * 
 * @tparam T Tipo de los elementos
 */
template <typename T> class SolucionVector : public Solucion {
 private:
  std::vector<T> datos_; 

 public:
  /**
   * @brief Constructor a partir de un vector
   * @param datos Vector de elementos ordenados
   */
  explicit SolucionVector(const std::vector<T>& datos) : datos_(datos) {}

  /**
   * @brief Permite acceder a los datos de la solución
   * @returns referencia constante al vector interno
   */
  const std::vector<T>& datos() const {
    return datos_;
  }

  /**
   * @brief Muestra la solución por pantalla
   * @param os flujo de salida
   */
  void mostrar(std::ostream& os) const override {
    os << "[ ";
    for (const auto& elem : datos_) {
      os << elem << " ";
    }
    os << "]";
  }
};

#endif